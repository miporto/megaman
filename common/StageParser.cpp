#include <vector>
#include <string>
#include <map>

#include "StageParser.h"
#include "extern/libjson/json.hpp"

using json = nlohmann::json;

StageParserPositions StageParser::positions_of
        (const std::string& info,
         const std::string& name,
         const std::string& object_name) {
    json json_file = json::parse(info);
    std::vector<std::vector<int>> positions;

    json json_positions = json_file[name][object_name];

    for (size_t i = 0; i < json_positions.size(); ++i){
        std::vector<int> position;
        position.push_back((int)json_positions[i]["x"]);
        position.push_back((int) json_positions[i]["y"]);
        position.push_back((int) json_positions[i]["direction"]);
        positions.push_back(position);
    }

    return positions;
}

StageParserInfo StageParser::stage_info(const std::string& info) {
    std::map<std::string, std::vector<std::vector<int>>> pos;

    std::vector<std::vector<int>> met_positions =
            this->positions_of(info, "spawn", "Met");
    pos["Met"] = met_positions;

    std::vector<std::vector<int>> bumby_positions =
            this->positions_of(info, "spawn", "Bumby");
    pos["Bumby"] = bumby_positions;

    std::vector<std::vector<int>> sniper_positions =
            this->positions_of(info, "spawn", "Sniper");
    pos["Sniper"] = sniper_positions;

    std::vector<std::vector<int>> jumping_sniper_positions =
            this->positions_of(info, "spawn", "JumpingSniper");
    pos["JumpingSniper"] = jumping_sniper_positions;

    std::vector<std::vector<int>> block_positions =
            this->positions_of(info, "object", "Block");
    pos["Block"] = block_positions;

    std::vector<std::vector<int>> stairs_positions =
            this->positions_of(info, "object", "Stairs");
    pos["Stairs"] = stairs_positions;

    std::vector<std::vector<int>> spike_positions =
            this->positions_of(info, "object", "Spike");
    pos["Spike"] = spike_positions;

    std::vector<std::vector<int>> cliff_positions =
            this->positions_of(info, "object", "Cliff");
    pos["Cliff"] = cliff_positions;

    return pos;
}

StageParser::~StageParser() {}
