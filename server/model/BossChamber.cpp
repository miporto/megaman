#include <unistd.h>
#include <string>
#include <vector>
#include <utility>
#include <map>

#include "server/communication/InfoMaker.h"
#include "BossChamber.h"
#include "server/communication/Match.h"
#include "server/communication/ServerCommunicator.h"
#include "Factory.h"

#define SLEEP_TIME_MICROSECONDS 100000

BossChamber::BossChamber(Match* match,
                         std::vector<ServerCommunicator*>& communicators,
                         EventQueue& events,
                         const char boss_id)
        : match(match), boss(BossFactory::boss(boss_id)), events(events) {
    // Players setting
    for (unsigned int i = 0; i < communicators.size(); ++i)
        this->players[communicators[i]->get_player()->get_name()]
                = communicators[i]->get_player();

    //Objects setting: Players, Boss, Default stage
    this->set(BossChamberFactory::chamber());
    for (std::map<std::string, Player*>::iterator it = this->players.begin();
         it != this->players.end();
         ++it) {
        it->second->new_megaman();
        this->add_game_object(it->second->get_megaman());
    }
    this->add_game_object(this->boss);

    // Making of ChamberInfo json for client
    this->match->notify_boss_chamber_info(this->status());
}

Player* BossChamber::player_with_name(const std::string& name) {
    std::map<std::string, Player*>::iterator it = this->players.find(name);

    if (it == this->players.end())
        throw StageError("There is no player with that name");

    return it->second;
}

void BossChamber::execute_action(Player* player,
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
        player->get_megaman()->shoot(this);
    } else if (AMMO_0 <= action_id && action_id <= AMMO_5 && pressed) {
        player->get_megaman()->change_ammo(action_id);
    } else {
        throw BossChamberError("There is no action with that id");
    }
}

void BossChamber::execute_events() {
    while (!this->events.is_empty()) {
        Action* action = this->events.pop();
        Player* player = this->player_with_name(action->get_name());
        this->execute_action(player,
                             action->get_action(), action->is_pressed());
        delete action;
    }
}

bool BossChamber::players_are_dead() {
    for (std::map<std::string, Player*>::iterator it = this->players.begin();
         it != this->players.end();
         ++it) { if (it->second->alive()) return false; }
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
    usleep(SLEEP_TIME_MICROSECONDS * 10^3);
    while (!*exit && !this->players_are_dead() && !this->boss->is_dead()) {
        this->execute_events();
        this->tick();
        this->check_collisions();
        //this->acknowledge_deceased();
        this->create_new_projectiles();
        this->acknowledge_updates();
        this->acknowledge_deceased();
        usleep(SLEEP_TIME_MICROSECONDS);
    }
}

bool BossChamber::beated() {
    return this->boss->is_dead();
}

void BossChamber::reward_players() {
    const std::string ammo_name = this->boss->reward_ammo_name();

    for (std::map<std::string, Player*>::iterator it = this->players.begin();
         it != this->players.end();
         ++it) { it->second->add_reward(ammo_name); }
}

BossChamber::~BossChamber() {}

BossChamberError::BossChamberError(const std::string error_msg) throw()
        : SystemError(error_msg) {}
