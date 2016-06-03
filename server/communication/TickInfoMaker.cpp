#include <vector>
#include <string>

#include "TickInfoMaker.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1
#define DIRECTION_X_POS 2
#define DIRECTION_Y_POS 3

void TickInfoMaker::add_player(const std::string& name,
                               std::vector<int> pos, int energy) {
    this->info["player"][name] = { {"x", pos[X_COORD_POS]},
                                   {"y", pos[Y_COORD_POS]},
                                   {"direction x", pos[DIRECTION_X_POS]},
                                   {"direction y", pos[DIRECTION_Y_POS]},
                                   {"energy", energy} };
}

void TickInfoMaker::add_enemy(const std::string& name,
                              std::vector<int> pos) {
    this->info["enemy"][name] = { {"x", pos[X_COORD_POS]},
                                  {"y", pos[Y_COORD_POS]},
                                  {"direction x", pos[DIRECTION_X_POS]},
                                  {"direction y", pos[DIRECTION_Y_POS]}};
}

void TickInfoMaker::add_projectile(const std::string& name,
                                   std::vector<int> pos) {
    this->info["projectile"][name] = { {"x", pos[X_COORD_POS]},
                                       {"y", pos[Y_COORD_POS]},
                                       {"direction x", pos[DIRECTION_X_POS]},
                                       {"direction y", pos[DIRECTION_Y_POS]}};
}

const std::string TickInfoMaker::str() { return this->info.dump(); }

TickInfoMaker::~TickInfoMaker() {}
