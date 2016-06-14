#include <unistd.h>
#include <string>
#include <vector>
#include <utility>
#include <server/Logger.h>

#include "Stage.h"
#include "server/communication/Match.h"
#include "server/communication/ServerCommunicator.h"
#include "Object.h"

#define SLEEP_TIME_MICROSECONDS 100

Stage::Stage(Match* match,
             std::vector<ServerCommunicator*>& communicators,
             EventQueue* events,
             const std::string& stage_info)
        : match(match), events(events), end_reached(false) {
    // Players setting
    for (unsigned int i = 0; i < communicators.size(); ++i)
        this->players.push_back(communicators[i]->get_player());

    // Map setting
    this->map.set(stage_info);
    for (unsigned int i = 0; i < this->players.size(); ++i) {
        this->players[i]->new_megaman();
        this->map.add_game_object(this->players[i]->get_megaman());
    }

//    // EventQueue setting
//    std::vector<PacketsQueueProtected*> action_queues;
//    for (unsigned int i = 0; i < communicators.size(); ++i)
//        action_queues.push_back(communicators[i]->get_actions());
//    this->events = new EventQueue(action_queues);

    // Making of StageInfo json for client
    this->match->notify_stage_info(this->map.status());
}

Player* Stage::player_with_name(const std::string& name) {
    for (unsigned int i = 0; i < this->players.size(); ++i) {
        if ((this->players[i]->get_name()).compare(name) == 0)
            return this->players[i];
    }
    throw StageError("There is no player with that name");
}

void Stage::execute_action(Player* player,
                          const char action_id, const bool pressed) {
    if (action_id == RIGHT) {
        player->get_megaman()->change_x_movement(pressed, true);
    } else if (action_id == LEFT) {
        player->get_megaman()->change_x_movement(pressed, false);
    } else if (action_id == UP) {
        player->get_megaman()->change_y_movement(pressed, true);
    } else if (action_id == DOWN) {
        player->get_megaman()->change_y_movement(pressed, false);
    } else if (action_id == SHOOT) {
        Projectile *projectile = player->get_megaman()->shoot();
        if (projectile) this->map.add_game_object(projectile);
    } else if (AMMO_0 <= action_id && action_id <= AMMO_5 && pressed) {
        player->get_megaman()->change_ammo(action_id);
    } else {
        throw StageError("There is no action with that id");
    }
}

void Stage::execute_events() {
    while (!this->events->is_empty()) {
        Action* action = this->events->pop();
        Player* player = this->player_with_name(action->get_name());
        this->execute_action(player,
                             action->get_action(), action->is_pressed());
        delete action;
    }
}

void Stage::tick() { this->map.tick(); }

void Stage::check_collisions() {
    try {
        this->map.check_collisions();
    } catch (const ObjectError& e) {
        this->end_reached = true;
    }
}

void Stage::acknowledge_deceased() {
    std::vector<int> deceased_ids = this->map.get_rid_of_corpses();
    for (unsigned int i = 0; i < deceased_ids.size(); ++i)
        this->match->notify_deceased(deceased_ids[i]);
}

void Stage::create_new_projectiles() {
    this->map.create_new_projectiles();
    //TODO send info de proyectiles nuevos
    // ahora o directamente en el proximo tick?
    //map me tiene que dar un vector de info de ellos
}

void Stage::acknowledge_updates() {
    std::vector<FloatUpdate*> updates = this->map.updates();
    for (unsigned int i = 0; i < updates.size(); ++i)
        this->match->notify_tick(updates[i]);
}

bool Stage::players_are_dead() {
    for (unsigned int i = 0; i < this->players.size(); ++i)
        if (this->players[i]->alive()) return false;
    std::cout << "Players are dead" << std::endl;
    return true;
}

void Stage::run(bool* exit) {
    usleep(SLEEP_TIME_MICROSECONDS * 10^6);
    while (!*exit && !this->players_are_dead() && !this->end_reached) {
        Logger::instance()->out << INFO << "Stage loop init";
        this->execute_events();
        this->tick();
        this->check_collisions();
        this->acknowledge_deceased();
        this->create_new_projectiles();
        this->acknowledge_updates();
        Logger::instance()->out << INFO << "Stage loop end";
        usleep(SLEEP_TIME_MICROSECONDS * 20);
    }
}

bool Stage::beated() { return !players_are_dead() && this->end_reached; }

Stage::~Stage() {
    delete this->events;
}

StageError::StageError(const std::string error_msg) throw()
        : SystemError(error_msg) {}
