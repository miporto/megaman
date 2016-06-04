#include <string>
#include <vector>

#include "TickInfoParser.h"
#include "extern/libjson/json.hpp"

using json = nlohmann::json;

TickInfoParser::TickInfoParser(const std::string &tick_info) :
        tick_info(tick_info){
    Coordinates met = coordinates_of("Met");
    tick_parser_info["Met"] = met;
}
TickParserInfo TickInfoParser::get_parsed_tick_info() {
    return tick_parser_info;
}
Coordinates TickInfoParser::coordinates_of(const std::string &actor) {
    json json_file = json::parse(tick_info);
    Coordinates coordinates;
    json json_positions = json_file[actor];
    for (size_t i = 0; i < json_positions.size(); ++i) {
        std::vector<int> coordinate;
        coordinate.push_back((int)json_positions[i]["x"]);
        coordinate.push_back((int)json_positions[i]["y"]);
        coordinate.push_back((int)json_positions[i]["direction x"]);
        coordinate.push_back((int)json_positions[i]["direction y"]);
        coordinates.push_back(coordinate);
    }
    return coordinates;
}
TickInfoParser::~TickInfoParser() {}
