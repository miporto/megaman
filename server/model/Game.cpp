#include <string>
#include <vector>

#include "server/communication/Match.h"
#include "Game.h"

class Match;

Game::Game(Match* match)
        : running(true), match(match) {}

void Game::new_player(MegaMan* player) {
    this->players.push_back(player);
    this->map.add_player(player);
}

void Game::set_event_queue
        (const std::vector<PacketsQueueProtected*>& action_queues) {
    this->events = new EventQueue(action_queues);
}

void Game::set_stage(const std::string& info) {
    this->map.set(info);
}

MegaMan* Game::player_with_name(const std::string& name) {
    for (unsigned int i = 0; i < this->players.size(); ++i) {
        if (this->players[i]->get_name() == name)
            return this->players[i];
    }
    return NULL; //No existe player con ese nombre
}

void Game::execute_action(MegaMan* player,
                          const char action_id, const bool pressed) {
    //TODO
}

void Game::execute_events() {
    while (!this->events->is_empty()) {
        Action* action = this->events->pop();
        MegaMan* player = this->player_with_name(action->get_name());
        this->execute_action(player,
                             action->get_action(), action->is_pressed());
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
    while (this->running) {
        this->execute_events();
        this->tick();
        this->get_rid_of_corpses();
        this->match->send_tick(this->status());
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
