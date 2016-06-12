#include <unistd.h>
#include <string>
#include <vector>

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
        if (projectile) this->add_projectile(projectile);
    } else {
        throw BossChamberError("There is no action with that id");
    }
}

void BossChamber::add_projectile(Projectile* projectile) {
    this->projectiles.push_back(projectile);
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

void BossChamber::run() {
    //TODO
    while (!this->players_are_dead() && !this->boss->is_dead()) {
        this->execute_events();
//        this->tick();
//        this->check_collisions();
//        this->get_rid_of_corpses();
//        this->create_new_projectiles();
//        this->match->notify_tick(this->status());
        usleep(SLEEP_TIME_MICROSECONDS);
    }
}

bool BossChamber::beated() {
    return this->boss->is_dead();
}

BossChamber::~BossChamber() {
    delete this->boss;
}

BossChamberError::BossChamberError(const std::string error_msg) throw()
        : SystemError(error_msg) {}
