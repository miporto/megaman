#include <map>
#include <string>

#include "GameInfo.h"

GameInfo::GameInfo(int initial_lives,
         int respawn_time,
         int cannon_ammo_max,
         std::map<std::string, int> velocities,
         std::map<std::string, int> initial_energy,
         std::map<std::string, int> damage) :
        initial_lives(initial_lives),
        respawn_time(respawn_time),
        cannon_ammo_max(cannon_ammo_max),
        velocities(velocities),
        initial_energy(initial_energy),
        damage(damage) {}

GameInfo::~GameInfo() {}
