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

int EnemyFactory::energy(const std::string& name) {
    json j_info = FileReader::read(INFO_FILE, "enemy");
    return (int) j_info[name]["energy"];
}

float EnemyFactory::velocity_x(const std::string& name) {
    json j_info = FileReader::read(INFO_FILE, "enemy");
    return (float) j_info[name]["velocity x"];
}

float EnemyFactory::velocity_y(const std::string& name) {
    json j_info = FileReader::read(INFO_FILE, "enemy");
    return (float) j_info[name]["velocity y"];
}

EnemyFactory::~EnemyFactory() {}

std::vector<float> MegaManFactory::respawn_point() {
    std::vector<float> respawn;
    json j_info = FileReader::read(INFO_FILE, "mega man");
    respawn.push_back((float) j_info["initial x"]);
    respawn.push_back((float) j_info["initial y"]);
    return respawn;
}

float MegaManFactory::velocity_x() {
    json j_info = FileReader::read(INFO_FILE, "mega man");
    return (float) j_info["velocity x"];
}

float MegaManFactory::velocity_y() {
    json j_info = FileReader::read(INFO_FILE, "mega man");
    return (float) j_info["velocity y"];
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
                                          const std::vector<float>& position) {
    json j_info = FileReader::read(INFO_FILE, "projectile");
    int damage = (int) j_info[name]["damage"];
    float velocity_x = (float) j_info[name]["velocity x"];
    float velocity_y = (float) j_info[name]["velocity y"];
    if (name == PLASMA_NAME) return new Plasma(damage, velocity_x,
                                               velocity_y, position);
    else if (name == BOMB_NAME) return new Bomb(damage, velocity_x,
                                                velocity_y, position);
    else if (name == MAGNET_NAME) return new Magnet(damage, velocity_x,
                                                    velocity_y, position);
    else if (name == SPARK_NAME) return new Spark(damage, velocity_x,
                                                  velocity_y, position);
    else if (name == FIRE_NAME) return new Fire(damage, velocity_x,
                                                velocity_y, position);
    else if (name == RING_NAME) return new Ring(damage, velocity_x,
                                                velocity_y, position);

    throw FactoryError("No projectile with that name");
}

ProjectileFactory::~ProjectileFactory() {}

Ammo* AmmoFactory::ammo(const std::string& name) {
    json j_info = FileReader::read(INFO_FILE, "ammo");
    int max = (int) j_info[name]["max"];
    return new Ammo(name, max);
}

AmmoFactory::~AmmoFactory() {}

Boss* BossFactory::boss(const char stage_id) {
    json j_info = FileReader::read(INFO_FILE, "stage");
    std::string boss_name = j_info["boss"]["name"];
    std::vector<float> initial_position;
    float initial_x = (float) j_info["boss"]["initial x"];
    float initial_y = (float) j_info["boss"]["initial y"];
    initial_position.push_back(initial_x);
    initial_position.push_back(initial_y);
    float velocity_x = (float) j_info["boss"]["velocity x"];
    float velocity_y = (float) j_info["boss"]["velocity y"];
    int energy = (int) j_info["boss"]["energy"];

    if (boss_name == BOMBMAN_NAME)
        return new BombMan(initial_position, velocity_x, velocity_y, energy);
    else if (boss_name == RINGMAN_NAME)
        return new RingMan(initial_position, velocity_x, velocity_y, energy);
    else if (boss_name == SPARKMAN_NAME)
        return new SparkMan(initial_position, velocity_x, velocity_y, energy);
    else if (boss_name == MAGNETMAN_NAME)
        return new MagnetMan(initial_position, velocity_x, velocity_y, energy);
    else if (boss_name == FIREMAN_NAME)
        return new FireMan(initial_position, velocity_x, velocity_y, energy);

    throw FactoryError("No boss with that name");
}

BossFactory::~BossFactory() {}

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
    json j_info = FileReader::read(INFO_FILE, "map");
    return (int) j_info["width"];
}

unsigned int MapFactory::height() {
    json j_info = FileReader::read(INFO_FILE, "map");
    return (int) j_info["height"];
}

MapFactory::~MapFactory() {}

FactoryError::FactoryError(const std::string error_msg) throw()
        : SystemError(error_msg) {}
