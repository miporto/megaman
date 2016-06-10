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
    StatusInfo mets = status_info_of("Met");
    new_tick_parser_info["Met"] = mets;
    StatusInfo megs = status_info_of("MegaMan");
    new_tick_parser_info["MegaMan"] = megs;

}

TickParserInfo TickInfoParser::get_parsed_tick_info() {
    return new_tick_parser_info;
}

std::map<std::string, std::string> TickInfoParser::parse_update(
        const std::string &info) {
    std::map<std::string, std::string> parsed_update;
    json json_update = json::parse(info);
    for (json::iterator it = json_update.begin(); it != json_update.end(); ++it)
    {
        std::string key = it.key();
        std::string value;
        if (it.value().is_number()) {
            int id = it.value();
            value = std::to_string(id);
        } else {
            value = it.value();
        }
        parsed_update[key] = value;
    }
    return parsed_update;
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
        if (element_info.count("direction x") != 0 && element_info.count
                ("direction y") != 0) {
            int x = element_info["direction ""x"];
            p_element_info["dir_x"] = std::to_string(x);
            int y = element_info["direction ""y"];
            p_element_info["dir_y"] = std::to_string(y);
        }
        status_info[element_info["id"]] = p_element_info;
        // TODO: add special info for actors
    }
    return status_info;
}

TickInfoParser::~TickInfoParser() {}
