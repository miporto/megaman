#include <string>
#include <vector>

#include "server/communication/Match.h"
#include "Game.h"

class Match;

Game::Game(Match* match)
        : running(true), match(match), events(NULL) {}

void Game::new_player(Player* player) {
    this->players.push_back(player);
}

void Game::set_event_queue
        (const std::vector<PacketsQueueProtected*>& action_queues) {
    this->events = new EventQueue(action_queues);
}

void Game::set_stage(const std::string& info) {
    this->map.set(info);
    for (unsigned int i = 0; i < this->players.size(); ++i) {
        this->players[i]->new_megaman();
        this->map.add_game_object(this->players[i]->get_megaman());
    }
}

Player* Game::player_with_name(const std::string& name) {
    for (unsigned int i = 0; i < this->players.size(); ++i) {
        std::cout << name << std::endl;
        std::cout << this->players[i]->get_name() << std::endl;
        if ((this->players[i]->get_name()).compare(name) == 0)
            return this->players[i];
    }
    return NULL; //No existe player con ese nombre
}

void Game::execute_action(Player* player,
                          const char action_id, const bool pressed) {
    if (action_id == RIGHT) {
        player->get_megaman()->change_x_movement(pressed, true);
    } else if (action_id == LEFT) {
        player->get_megaman()->change_x_movement(pressed, false);
    } else if (action_id == UP) {
        player->get_megaman()->change_y_movement(pressed, true);
    } else if (action_id == SHOOT) {
        Projectile* projectile = player->get_megaman()->shoot();
        if (projectile) this->map.add_game_object(projectile);
    }
}

void Game::execute_events() {
    while (!this->events->is_empty()) {
        Action* action = this->events->pop();
        Player* player = this->player_with_name(action->get_name());
        this->execute_action(player,
                             action->get_action(), action->is_pressed());
        delete action;
    }
}

void Game::tick() {
    this->map.tick();
}

void Game::check_collisions() {
    this->map.check_collisions();
}

void Game::get_rid_of_corpses() {
    this->map.get_rid_of_corpses();
}

void Game::create_new_projectiles() {
    this->map.create_new_projectiles();
}

const std::string Game::status() {
    return this->map.status();
}

void Game::run() {
    while (this->running) {
        this->execute_events();
        this->tick();
        this->check_collisions();
        this->get_rid_of_corpses();
        this->create_new_projectiles();
        this->match->notify_tick(this->status());
    }
}

void Game::quit() {
    this->running = false;
}

Game::~Game() {
    this->quit();
    this->join();
    for (unsigned int i = 0; i < this->players.size(); ++i)
        delete this->players[i];
    delete this->events;
}
