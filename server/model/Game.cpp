#include <string>

#include "Game.h"

void Game::new_player(std::string& name) {
    this->players.push_back(new Player(name));
}

void Game::set_stage(StageInfo* info) {
    this->map.set(info);
}

void Game::tick() {
    map.tick();
}

Game::~Game() {
    for (unsigned int i = 0; i < this->players.size(); ++i)
        delete this->players[i];
}
