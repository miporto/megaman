#include <vector>
#include <string>
#include <map>

#include "GameObjectParser.h"
#include "extern/libjson/json.hpp"

using json = nlohmann::json;

GameObjectParserPositions GameObjectParser::positions_of
        (const std::string& info,
         const std::string& name,
         const std::string& object_name) {
    json json_file = json::parse(info);

    std::vector<std::vector<float>> positions;

    json json_positions = json_file[name][object_name];

    for (size_t i = 0; i < json_positions.size(); ++i){
        std::vector<float> position;
        position.push_back((float)json_positions[i]["x"]);
        position.push_back((float) json_positions[i]["y"]);
        positions.push_back(position);
    }

    return positions;
}

GameObjectParserInfo GameObjectParser::stage_info(const std::string& info) {
    std::map<std::string, std::vector<std::vector<float>>> pos;

    std::vector<std::vector<float>> met_positions =
            this->positions_of(info, "spawn", "Met");
    pos["Met"] = met_positions;

    std::vector<std::vector<float>> bumby_positions =
            this->positions_of(info, "spawn", "Bumby");
    pos["Bumby"] = bumby_positions;

    std::vector<std::vector<float>> sniper_positions =
            this->positions_of(info, "spawn", "Sniper");
    pos["Sniper"] = sniper_positions;

    std::vector<std::vector<float>> jumping_sniper_positions =
            this->positions_of(info, "spawn", "JumpingSniper");
    pos["JumpingSniper"] = jumping_sniper_positions;

    std::vector<std::vector<float>> block_positions =
            this->positions_of(info, "object", "Block");
    pos["Block"] = block_positions;

    std::vector<std::vector<float>> stairs_positions =
            this->positions_of(info, "object", "Stairs");
    pos["Stairs"] = stairs_positions;

    std::vector<std::vector<float>> spike_positions =
            this->positions_of(info, "object", "Spike");
    pos["Spike"] = spike_positions;

    std::vector<std::vector<float>> door_positions =
            this->positions_of(info, "object", "Door");
    pos["Door"] = door_positions;

    std::vector<std::vector<float>> cliff_positions =
            this->positions_of(info, "object", "Cliff");
    pos["Cliff"] = cliff_positions;

    return pos;
}

GameObjectParser::~GameObjectParser() {}
