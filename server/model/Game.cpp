#include <string>

#include "server/communication/Match.h"
#include "Game.h"

class Match;

Game::Game(Match* match, EventQueue* events)
        : match(match), events(events) {}

void Game::new_player(Player* player) {
    this->map.add_player(player);
}

void Game::set_stage(const std::string& info) {
    this->map.set(info);
}

void Game::execute_events() {
    while (!this->events->is_empty()) {
        Action* action = this->events->pop();
        //TODO execute event
        delete action;
    }
}

void Game::tick() {
    map.tick();
}

void Game::get_rid_of_corpses() {
    map.get_rid_of_corpses();
}

const std::string Game::status() {
    return map.status();
}

void Game::run() {
    this->execute_events();
    this->tick();
    this->get_rid_of_corpses();
    this->match->send_tick(this->status());
}

Game::~Game() {}
