#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <common/communication/Packet.h>

#include "extern/libjson/json.hpp"
#include "Factory.h"

#define INFO_FILE "info.json"

int EnemyFactory::energy(std::string name) {
    //TODO leer .JSON
    return 0;
}

int EnemyFactory::velocity(std::string name) {
    //TODO leer .JSON
    return 0;
}

EnemyFactory::~EnemyFactory() {}

int MegaManFactory::velocity() {
    //TODO leer .JSON
    return 0;
}

MegaManFactory::~MegaManFactory() {}

int EnergyTankFactory::initial_lives() {
    //TODO leer .JSON
    return 0;
}

int EnergyTankFactory::maximum_energy() {
    //TODO leer .JSON
    return 0;
}

EnergyTankFactory::~EnergyTankFactory() {}

Projectile* ProjectileFactory::projectile(const std::string& name,
                                          const std::vector<int>& position) {
    //TODO leer .JSON
    // TODO la position que se recibe es la inicial del proyectil
    return NULL;
}

ProjectileFactory::~ProjectileFactory() {}

Ammo* AmmoFactory::ammo(const std::string& name) {
    //TODO leer .JSON
    return NULL;
}

AmmoFactory::~AmmoFactory() {}

const std::string StageFactory::initial_stage(const char stage_id) {
    std::ifstream game_info(INFO_FILE);
    std::string file_dump, buffer;
    while (getline(game_info, buffer))
        file_dump += buffer;
    game_info.close();
    json json_file = json::parse(file_dump);

    int i = stage_id;
    std::stringstream ss;
    std::string s_stage_id;
    ss << i;
    ss >> s_stage_id;

    json j_stage = json_file["stage"][s_stage_id];
    return j_stage.dump();
}

StageFactory::~StageFactory() {}

unsigned int MapFactory::width() {
    //TODO leer .JSON
    return 0;
}

unsigned int MapFactory::height() {
    //TODO leer .JSON
    return 0;
}

MapFactory::~MapFactory() {}
