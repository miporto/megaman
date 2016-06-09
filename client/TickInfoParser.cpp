#include <map>
#include <string>
#include <vector>

#include "TickInfoParser.h"
#include "extern/libjson/json.hpp"

using json = nlohmann::json;

TickInfoParser::TickInfoParser(const std::string &tick_info) :
        tick_info(tick_info){
    json_info = json::parse(tick_info);

    StatusInfo block = status_info_of("Block");
    new_tick_parser_info["Block"] = block;
    StatusInfo stairs = status_info_of("Stairs");
    new_tick_parser_info["Stairs"] = stairs;
//    StatusInfo spikes = status_info_of("Spikes");
//    new_tick_parser_info["Spikes"] = spikes;

    // Old stuff
//    Coordinates met = coordinates_of("Met");
//    tick_parser_info["Met"] = met;
//    Coordinates megaman = coordinates_of("MegaMan");
//    tick_parser_info["MegaMan"] = megaman;
//    Coordinates prellet = coordinates_of("Pellet");
//    tick_parser_info["Pellet"] = prellet;
}

NewTickParserInfo TickInfoParser::get_new_parsed_tick_info() {
    return new_tick_parser_info;
}
TickParserInfo TickInfoParser::get_parsed_tick_info() {
    return tick_parser_info;
}
StatusInfo TickInfoParser::status_info_of(const std::string &element) {
    StatusInfo status_info;
    json elements_info = json_info[element];
    std::map<std::string, std::string> p_element_info;
    for (size_t i = 0; i < elements_info.size(); ++i) {
        std::string s_element_info = elements_info[i];
        json element_info = json::parse(s_element_info);
        // TODO: id is an int
        p_element_info["x"] = element_info["x"];
        p_element_info["y"] = element_info["y"];
        status_info[element_info["id"]] = p_element_info;
        // TODO: add special info for actors
    }
    return status_info;
}
Coordinates TickInfoParser::coordinates_of(const std::string &actor) {
    Coordinates coordinates;
    json json_positions = json_info[actor];
    for (size_t i = 0; i < json_positions.size(); ++i) {
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
