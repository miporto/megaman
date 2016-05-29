#include <vector>
#include <string>
#include <map>

#include "StageParser.h"
#include "extern/libjson/json.hpp"

using json = nlohmann::json;

StageParserPositions StageParser::positions_of
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

StageParserInfo StageParser::stage_info(const std::string& info) {
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

StageParser::~StageParser() {}
