#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <common/communication/Packet.h>

#include "extern/libjson/json.hpp"
#include "Factory.h"

#define INFO_FILE "info.json"

json FileReader::read(const std::string& file_name,
                      const std::string& branch_name) {
    std::ifstream file(file_name);
    std::string file_dump, buffer;
    while (getline(file, buffer))
        file_dump += buffer;
    file.close();
    json json_file = json::parse(file_dump);
    return json_file[branch_name];
}

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
    json j_info = FileReader::read(INFO_FILE, "info");
    return (int) j_info["energy_tank"]["initial_lives"];
}

int EnergyTankFactory::maximum_energy() {
    json j_info = FileReader::read(INFO_FILE, "info");
    return (int) j_info["energy_tank"]["max_energy"];
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
    json json_file = FileReader::read(INFO_FILE, "stage");

    int i = stage_id;
    std::stringstream ss;
    std::string s_stage_id;
    ss << i;
    ss >> s_stage_id;

    json j_stage = json_file[s_stage_id];
    return j_stage.dump();
}

StageFactory::~StageFactory() {}

unsigned int MapFactory::width() {
//    json j_info = FileReader::read(INFO_FILE, "info");
//    return (int) j_info["map"]["width"];
    return 0;
}

unsigned int MapFactory::height() {
//    json j_info = FileReader::read(INFO_FILE, "info");
//    return (int) j_info["map"]["height"];
    return 0;
}

MapFactory::~MapFactory() {}
