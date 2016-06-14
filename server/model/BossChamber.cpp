#include <unistd.h>
#include <string>
#include <vector>
#include <utility>

#include "server/communication/InfoMaker.h"
#include "BossChamber.h"
#include "server/communication/Match.h"
#include "server/communication/ServerCommunicator.h"
#include "Factory.h"

#define SLEEP_TIME_MICROSECONDS 10

BossChamber::BossChamber(Match* match,
                         std::vector<ServerCommunicator*>& communicators,
                         const char boss_id)
        : match(match), boss(BossFactory::boss(boss_id)), events(NULL) {
    // Players setting
    for (unsigned int i = 0; i < communicators.size(); ++i)
        this->players.push_back(communicators[i]->get_player());

    // EventQueue setting
    std::vector<PacketsQueueProtected*> action_queues;
    for (unsigned int i = 0; i < communicators.size(); ++i)
        action_queues.push_back(communicators[i]->get_actions());
    this->events = new EventQueue(action_queues);

    //Objects setting: Players, Boss, Default stage
    this->set(BossChamberFactory::chamber());
    for (unsigned int i = 0; i < this->players.size(); ++i) {
        this->players[i]->new_megaman();
        this->add_game_object(this->players[i]->get_megaman());
    }
    this->add_game_object(this->boss);

    // Making of ChamberInfo json for client
    this->match->notify_boss_chamber_info(this->status());
}

Player* BossChamber::player_with_name(const std::string& name) {
    for (unsigned int i = 0; i < this->players.size(); ++i) {
        if ((this->players[i]->get_name()).compare(name) == 0)
            return this->players[i];
    }
    throw BossChamberError("There is no player with that name");
}

void BossChamber::execute_action(Player* player,
                           const char action_id, const bool pressed) {
    if (action_id == RIGHT) {
        player->get_megaman()->change_x_movement(pressed, true);
    } else if (action_id == LEFT) {
        player->get_megaman()->change_x_movement(pressed, false);
    } else if (action_id == UP) {
        player->get_megaman()->change_y_movement(pressed, true);
    } else if (action_id == SHOOT) {
        Projectile *projectile = player->get_megaman()->shoot();
        if (projectile) this->add_game_object(projectile);
    } else {
        throw BossChamberError("There is no action with that id");
    }
}

void BossChamber::execute_events() {
    while (!this->events->is_empty()) {
        Action* action = this->events->pop();
        Player* player = this->player_with_name(action->get_name());
        this->execute_action(player,
                             action->get_action(), action->is_pressed());
        delete action;
    }
}

bool BossChamber::players_are_dead() {
    for (unsigned int i = 0; i < this->players.size(); ++i)
        if (this->players[i]->alive()) return false;
    return true;
}

void BossChamber::acknowledge_deceased() {
    std::vector<int> deceased_ids = this->get_rid_of_corpses();
    for (unsigned int i = 0; i < deceased_ids.size(); ++i)
        this->match->notify_deceased(deceased_ids[i]);
}

void BossChamber::acknowledge_updates() {
    std::vector<FloatUpdate*> updates = this->updates();
    for (unsigned int i = 0; i < updates.size(); ++i)
        this->match->notify_tick(updates[i]);
}

void BossChamber::run(bool* exit) {
    while (!*exit && !this->players_are_dead() && !this->boss->is_dead()) {
        this->execute_events();
        this->tick();
        this->check_collisions();
        this->acknowledge_deceased();
        this->create_new_projectiles();
        this->acknowledge_updates();
        usleep(SLEEP_TIME_MICROSECONDS);
    }
}

bool BossChamber::beated() {
    return this->boss->is_dead();
}

void BossChamber::reward_players() {
    const std::string ammo_name = this->boss->reward_ammo_name();
    for (unsigned int i = 0; i < this->players.size(); ++i)
        this->players[i]->add_reward(ammo_name);
}

BossChamber::~BossChamber() {}

BossChamberError::BossChamberError(const std::string error_msg) throw()
        : SystemError(error_msg) {}
