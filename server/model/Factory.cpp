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

StageFactory::StageFactory() {
    std::ifstream game_info(INFO_FILE);
    std::string file_dump, buffer;
    while (getline(game_info, buffer))
        file_dump += buffer;
    game_info.close();
    json json_file = json::parse(file_dump);
    this->stage_json = json_file["stage"];
}

const std::string StageFactory::initial_stage(const char stage_id) {
    int i = stage_id;
    std::stringstream ss;
    std::string s_stage_id;
    ss << i;
    ss >> s_stage_id;
    json j_stage = this->stage_json[s_stage_id];
    return j_stage.dump();
}

StageFactoryPositions StageFactory::positions_of
        (const std::string& info,
         const std::string& name,
         const std::string& object_id) {
    json json_file = json::parse(info);
    std::vector<std::vector<int>> positions;

    json json_positions = json_file[name][object_id];

    for (size_t i = 0; i < json_positions.size(); ++i){
        std::vector<int> position;
        position.push_back((int)json_positions[i]["x"]);
        position.push_back((int) json_positions[i]["y"]);
        position.push_back((int) json_positions[i]["direction"]);
        positions.push_back(position);
    }

    return positions;
}

StageFactoryInfo StageFactory::stage_info(const std::string& info) {
    std::map<std::string, std::vector<std::vector<int>>> pos;

    std::vector<std::vector<int>> met_positions =
            this->positions_of(info, "spawn", "met");
    pos["met"] = met_positions;

    std::vector<std::vector<int>> bumby_positions =
            this->positions_of(info, "spawn", "bumby");
    pos["bumby"] = met_positions;

    std::vector<std::vector<int>> sniper_positions =
            this->positions_of(info, "spawn", "sniper");
    pos["sniper"] = met_positions;

    std::vector<std::vector<int>> jumping_sniper_positions =
            this->positions_of(info, "spawn", "jumping sniper");
    pos["jumping sniper"] = met_positions;

    std::vector<std::vector<int>> block_positions =
            this->positions_of(info, "object", "block");
    pos["block"] = met_positions;

    std::vector<std::vector<int>> stairs_positions =
            this->positions_of(info, "object", "stairs");
    pos["stairs"] = met_positions;

    std::vector<std::vector<int>> spike_positions =
            this->positions_of(info, "object", "spike");
    pos["spike"] = met_positions;

    std::vector<std::vector<int>> cliff_positions =
            this->positions_of(info, "object", "cliff");
    pos["cliff"] = met_positions;

    return pos;
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
