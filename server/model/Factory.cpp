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

FileReader::~FileReader() {}

int EnemyFactory::energy(std::string name) {
    json j_info = FileReader::read(INFO_FILE, "enemy");
    return (int) j_info[name]["energy"];
}

int EnemyFactory::velocity(std::string name) {
    json j_info = FileReader::read(INFO_FILE, "enemy");
    return (int) j_info[name]["velocity"];
}

EnemyFactory::~EnemyFactory() {}

int MegaManFactory::velocity() {
    json j_info = FileReader::read(INFO_FILE, "mega man");
    return (int) j_info["velocity"];
}

MegaManFactory::~MegaManFactory() {}

int EnergyTankFactory::initial_lives() {
    json j_info = FileReader::read(INFO_FILE, "energy tank");
    return (int) j_info["initial lives"];
}

int EnergyTankFactory::maximum_energy() {
    json j_info = FileReader::read(INFO_FILE, "energy tank");
    return (int) j_info["max"];
}

EnergyTankFactory::~EnergyTankFactory() {}

Projectile* ProjectileFactory::projectile(const std::string& name,
                                          const std::vector<int>& position) {
    json j_info = FileReader::read(INFO_FILE, "projectile");
    int damage = j_info[name]["damage"];
    int velocity = j_info[name]["velocity"];
    if (name == "plasma") return new Plasma(damage, velocity, position);
    else if (name == "bomb") return new Bomb(damage, velocity, position);
    else if (name == "magnet") return new Magnet(damage, velocity, position);
    else if (name == "spark") return new Spark(damage, velocity, position);
    else if (name == "fire") return new Fire(damage, velocity, position);
    else if (name == "ring") return new Ring(damage, velocity, position);
    return NULL;
}

ProjectileFactory::~ProjectileFactory() {}

Ammo* AmmoFactory::ammo(const std::string& name) {
    json j_info = FileReader::read(INFO_FILE, "ammo");
    int max = (int) j_info[name]["max"];
    return new Ammo(name, max);
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
    json j_info = FileReader::read(INFO_FILE, "info");
    return (int) j_info["map"]["width"];
}

unsigned int MapFactory::height() {
    json j_info = FileReader::read(INFO_FILE, "info");
    return (int) j_info["map"]["height"];
}

MapFactory::~MapFactory() {}
