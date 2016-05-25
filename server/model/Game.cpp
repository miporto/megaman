#include <string>

#include "Game.h"

void Game::new_player(std::string& name) {
    this->players.push_back(new Player(name));
}

void Game::set_stage(StageInfo* info) {
    this->map.set(info);
}

void Game::get_rid_of_corpses() {
    for (unsigned int i = 0; i < this->players.size(); ++i)
        if (this->players[i]->is_dead()) {
            //TODO que se hace cuando un jugador muere
        }
    map.get_rid_of_corpses();
}

void Game::tick() {
    this->get_rid_of_corpses();
    map.tick();
}

Game::~Game() {
    for (unsigned int i = 0; i < this->players.size(); ++i)
        delete this->players[i];
}
