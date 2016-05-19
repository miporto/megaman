#include <vector>
#include <string>

#include "Factory.h"

int EnergyTankFactory::initial_lives() {
    //TODO leer .JSON
    return 0;
}

int EnergyTankFactory::maximum_energy() {
    //TODO leer .JSON
    return 0;
}

EnergyTankFactory::~EnergyTankFactory() {}

Projectile* ProjectileFactory::operator()(const std::string& name) {
    //TODO leer .JSON
    return NULL;
}

ProjectileFactory::~ProjectileFactory() {}

Ammo* AmmoFactory::operator()(const std::string& name) {
    //TODO leer .JSON
    return NULL;
}

AmmoFactory::~AmmoFactory() {}

StageFactory::StageFactory(char id) : id(id) {}

std::vector<char> StageFactory::positions_of_spawns
        (const int screen, const int enemy_id) {
    std::vector<char> positions;
    //TODO leer .JSON
    return positions;
}

std::vector<char> StageFactory::positions_of_objects
        (const int screen, const int object_id) {
    std::vector<char> positions;
    //TODO leer .JSON
    return positions;
}

ScreenInfo* StageFactory::screen_info(const int screen) {
    //TODO crean ScreenInfo con metodos anteriores
    return NULL;
}

StageFactory::~StageFactory() {}
