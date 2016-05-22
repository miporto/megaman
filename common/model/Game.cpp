#include <string>

#include "Game.h"

void Game::set(GameInfo* info) {
    this->info = info;
}

void Game::new_player(std::string& name) {
    //Sacar de GameInfo atributos faltantes de Player
    this->players.push_back(new Player(name));
}

void Game::start_stage(StageInfo* info) {
    this->map.set(info);
}

Game::~Game() {
    for (unsigned int i = 0; i < this->players.size(); ++i)
        delete this->players[i];
}
