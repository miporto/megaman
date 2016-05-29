#include <vector>
#include <string>

#include "TickInfoMaker.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1
#define DIRECTION_POS 2

void TickInfoMaker::add_player(const std::string& name,
                               std::vector<int> pos, int energy) {
    this->info["player"][name] = { {"x", pos[X_COORD_POS]},
                                   {"y", pos[Y_COORD_POS]},
                                   {"direction", pos[DIRECTION_POS]},
                                   {"energy", energy} };
}

void TickInfoMaker::add_enemy(const std::string& name,
                              std::vector<int> pos) {
    this->info["enemy"][name] = { {"x", pos[X_COORD_POS]},
                                  {"y", pos[Y_COORD_POS]},
                                  {"direction", pos[DIRECTION_POS]} };
}

void TickInfoMaker::add_projectile(const std::string& name,
                                   std::vector<int> pos) {
    this->info["projectile"][name] = { {"x", pos[X_COORD_POS]},
                                       {"y", pos[Y_COORD_POS]},
                                       {"direction", pos[DIRECTION_POS]} };
}

const std::string TickInfoMaker::str() { return this->info.dump(); }

TickInfoMaker::~TickInfoMaker() {}
