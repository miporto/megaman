#include <vector>
#include <string>
#include <fstream>
#include <string>
#include <sstream>

#include "Factory.h"
#include "Cannon.h"
#include "extern/json.hpp"
#include "common/Position.h"

using json = nlohmann::json;

#define INFO_FILE "info.json"
#define STAGE "stage"
#define SPAWN "spawn"
#define OBJ "object"
#define X_COORD "x"
#define Y_COORD "y"
#define INFO "info"
#define ENERGY_TANK "energy_tank"
#define INITIAL_LIVES "initial_lives"
#define MAX_ENERGY "max_energy"
#define PROJECTILE "projectile"
#define DAMAGE "damage"
#define VELOCITY "velocity"
#define AMMO "ammo"
#define MAX_AMMO "max_ammo"
#define PLASMA "plasma"
#define BOMB "bomb"
#define MAGNET "magnet"
#define SPARK "spark"
#define FIRE "fire"
#define RING "ring"
#define MET_ID 1
#define BUMBY_ID 2
#define SNIPER_ID 3
#define JUMPING_SNIPER_ID 4
#define BLOCK_ID 4
#define STAIRS_ID 5
#define SPIKE_ID 6

EnergyTankFactory::EnergyTankFactory() {
    std::ifstream info(INFO_FILE);
    // ToDo: check if the file was properly opened (is_open). 
    // If not, raise an exception
    std::string file_dump;
    std::string buffer;
    while (getline(info, buffer)) file_dump += buffer;
    info.close();
    json json_file = json::parse(file_dump);
    this->info = json_file[INFO][ENERGY_TANK];
}

int EnergyTankFactory::initial_lives() {
    return info[INITIAL_LIVES];
}

int EnergyTankFactory::maximum_energy() {
    return info[MAX_ENERGY];
}

EnergyTankFactory::~EnergyTankFactory() {}

ProjectileFactory::ProjectileFactory() {
    std::ifstream info(INFO_FILE);
    // ToDo: check if the file was properly opened (is_open). 
    // If not, raise an exception
    std::string file_dump;
    std::string buffer;
    while (getline(info, buffer)) file_dump += buffer;
    info.close();
    json json_file = json::parse(file_dump);
    this->info = json_file[INFO][PROJECTILE];
}

Projectile* ProjectileFactory::operator()(const std::string& name,
                                          Position& position) {
    int damage = info[name][DAMAGE];
    int velocity = info[name][VELOCITY];
    std::string plasma(PLASMA);
    std::string bomb(BOMB);
    std::string magnet(MAGNET);
    std::string spark(SPARK);
    std::string fire(FIRE);
    if (name == plasma) return new Plasma(damage, velocity, position);
    else if (name == bomb) return new Bomb(damage, velocity, position);
    else if (name == magnet) return new Magnet(damage, velocity, position);
    else if (name == spark) return new Spark(damage, velocity, position);
    else if (name == fire) return new Fire(damage, velocity, position);
    else
        return new Ring(damage, velocity, position);
}

ProjectileFactory::~ProjectileFactory() {}

AmmoFactory::AmmoFactory() {
    std::ifstream info(INFO_FILE);
    // ToDo: check if the file was properly opened (is_open). 
    // If not, raise an exception
    std::string file_dump;
    std::string buffer;
    while (getline(info, buffer)) file_dump += buffer;
    info.close();
    json json_file = json::parse(file_dump);
    this->info = json_file[INFO][AMMO]; 
}

Ammo* AmmoFactory::operator()(const std::string& name) {
    std::string aux(name);
    return new Ammo(aux, (int)info[name][MAX_AMMO]);
}

AmmoFactory::~AmmoFactory() {}

std::vector<Position> StageFactory::positions_of
    (const char* type, const int object_id) {
    std::vector<Position> positions;
    // JSON ids cannot be numbers
    std::stringstream ss;
    ss << object_id;
    std::string s_object_id = ss.str();

    for (size_t i = 0; i < this->stage_json[type][s_object_id].size(); 
        ++i){
        int x = (int)this->stage_json[type][s_object_id][X_COORD];
        int y = (int)this->stage_json[type][s_object_id][Y_COORD];
        positions.push_back(Position(x, y));
    }

    return positions;
}

StageInfo* StageFactory::operator()(const int stage_id) {
    std::ifstream stage_info(INFO_FILE);
    // ToDo: check if the file was properly opened (is_open). 
    // If not, raise an exception
    std::string file_dump;
    std::string buffer;
    while (getline(stage_info, buffer)) file_dump += buffer;
    stage_info.close();
    json json_file = json::parse(file_dump);
    
    // JSON ids cannot be numbers
    std::stringstream ss;
    ss << stage_id;
    std::string s_id = ss.str();

    this->stage_json = json_file[STAGE][s_id];

    std::vector<Position> met_positions = 
        this->positions_of(SPAWN, MET_ID);
    
    std::vector<Position> bumby_positions =
        this->positions_of(SPAWN, BUMBY_ID);
    
    std::vector<Position> sniper_positions = 
        this->positions_of(SPAWN, SNIPER_ID);
    
    std::vector<Position> jumping_sniper_positions = 
        this->positions_of(SPAWN, JUMPING_SNIPER_ID);
    
    std::vector<Position> block_positions = 
        this->positions_of(OBJ, BLOCK_ID);
    
    std::vector<Position> stairs_positions = 
        this->positions_of(OBJ, STAIRS_ID);
    
    std::vector<Position> spike_positions = 
        this->positions_of(OBJ, SPIKE_ID);
    
    StageInfo* ret_value = new StageInfo( met_positions,
                                            bumby_positions,
                                            sniper_positions,
                                            jumping_sniper_positions,
                                            block_positions,
                                            stairs_positions,
                                            spike_positions);
    return ret_value;
}

StageFactory::~StageFactory() {}
