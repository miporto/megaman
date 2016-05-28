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
    std::ifstream stage_info(INFO_FILE);
    std::string file_dump, buffer;
    while (getline(stage_info, buffer))
        file_dump += buffer;
    stage_info.close();
    json json_file = json::parse(file_dump);

    this->stage_json = json_file["stage"];
}

std::vector<Position*> StageFactory::positions_of
        (const std::string& stage_id,
         const std::string& name,
         const std::string& object_id) {
    std::vector<Position*> positions;

    json j_positions = this->stage_json[stage_id][name][object_id];

    for (size_t i = 0; i < j_positions.size(); ++i){
        int x = (int) j_positions[i]["x"];
        int y = (int) j_positions[i]["y"];
        int direction = (int) j_positions[i]["direction"];
        positions.push_back(new Position(x, y, direction));
    }

    return positions;
}
std::map<char, StageInfo*> StageFactory::stage_info() {
    std::map<char, StageInfo*> stages;

    for (unsigned int i = 0; i < this->stage_json.size(); ++i) {
        std::stringstream ss;
        ss << (i + 1);
        std::string stage_id = ss.str();

        std::vector<Position*> met_positions =
                this->positions_of(stage_id, "spawn", "met");

        std::vector<Position*> bumby_positions =
                this->positions_of(stage_id, "spawn", "bumby");

        std::vector<Position*> sniper_positions =
                this->positions_of(stage_id, "spawn", "sniper");

        std::vector<Position*> jumping_sniper_positions =
                this->positions_of(stage_id, "spawn", "jumping sniper");

        std::vector<Position*> block_positions =
                this->positions_of(stage_id, "object", "block");

        std::vector<Position*> stairs_positions =
                this->positions_of(stage_id, "object", "stairs");

        std::vector<Position*> spike_positions =
                this->positions_of(stage_id, "object", "spike");

        std::vector<Position*> cliff_positions =
                this->positions_of(stage_id, "object", "cliff");

        stages[i] = new StageInfo(met_positions,
                                  bumby_positions,
                                  sniper_positions,
                                  jumping_sniper_positions,
                                  block_positions,
                                  stairs_positions,
                                  spike_positions,
                                  cliff_positions);
    }

    return stages;
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
