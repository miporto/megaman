#include <string>
#include <vector>

#include "server/communication/Match.h"
#include "Game.h"

class Match;

Game::Game(Match* match)
        : match(match) {}

void Game::new_player(Player* player) {
    this->map.add_player(player);
}

void Game::set_event_queue
        (const std::vector<PacketsQueueProtected*>& action_queues) {
    this->events = new EventQueue(action_queues);
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

Game::~Game() {
    delete this->events;
}
