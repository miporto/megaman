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

Projectile* ProjectileFactory::operator()(const std::string& name,
                                          Position& position) {
    //TODO leer .JSON
    // TODO la position que se recibe es la inicial del proyectil
    return NULL;
}

ProjectileFactory::~ProjectileFactory() {}

Ammo* AmmoFactory::operator()(const std::string& name) {
    //TODO leer .JSON
    return NULL;
}

AmmoFactory::~AmmoFactory() {}

std::vector<char> StageFactory::positions_of_spawns
        (const int stage_id, const int enemy_id) {
    std::vector<char> positions;
    //TODO leer .JSON
    return positions;
}

std::vector<char> StageFactory::positions_of_objects
        (const int stage_id, const int object_id) {
    std::vector<char> positions;
    //TODO leer .JSON
    return positions;
}

StageInfo* StageFactory::operator()(const int stage_id) {
    //TODO crean StageInfo con metodos anteriores
    return NULL;
}

StageFactory::~StageFactory() {}
