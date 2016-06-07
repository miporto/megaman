#include <string>
#include <vector>

#include "TickInfoParser.h"
#include "extern/libjson/json.hpp"

using json = nlohmann::json;

TickInfoParser::TickInfoParser(const std::string &tick_info) :
        tick_info(tick_info){
    Coordinates met = coordinates_of("Met");
    tick_parser_info["Met"] = met;
    Coordinates megaman = coordinates_of("MegaMan");
    tick_parser_info["MegaMan"] = megaman;
    Coordinates prellet = coordinates_of("Pellet");
    tick_parser_info["Pellet"] = prellet;
}
TickParserInfo TickInfoParser::get_parsed_tick_info() {
    return tick_parser_info;
}
Coordinates TickInfoParser::coordinates_of(const std::string &actor) {
    json json_file = json::parse(tick_info);
    Coordinates coordinates;
    json json_positions = json_file[actor];
    for (size_t i = 0; i < json_positions.size(); ++i) {
        std::cout << json_positions.dump() << std::endl;
        std::cout << json_positions[i] << std::endl;
        std::string s_json_position = json_positions[i];
        std::vector<int> coordinate;
        json json_position = json::parse(s_json_position);
        coordinate.push_back((int)json_position["x"]);
        coordinate.push_back((int)json_position["y"]);
//        coordinate.push_back((int)json_position["direction x"]);
//        coordinate.push_back((int)json_position["direction y"]);
        coordinates.push_back(coordinate);
    }
    return coordinates;
}
TickInfoParser::~TickInfoParser() {}
