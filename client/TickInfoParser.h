#ifndef TICKINFOPARSER_H
#define TICKINFOPARSER_H

#include <map>
#include <string>
#include <vector>

#include "extern/libjson/json.hpp"

using json = nlohmann::json;

typedef std::map<int, std::map<std::string, std::string>> StatusInfo;
typedef std::map<std::string, StatusInfo> NewTickParserInfo;
typedef std::vector<std::vector<int>> Coordinates;
typedef std::map<std::string, Coordinates> TickParserInfo;

class TickInfoParser {
public:
    explicit TickInfoParser(const std::string& tick_info);
    TickParserInfo get_parsed_tick_info();
    NewTickParserInfo get_new_parsed_tick_info();
    ~TickInfoParser();
private:
    Coordinates coordinates_of(const std::string& actor);
    StatusInfo status_info_of(const std::string& element);
    std::string tick_info;
    TickParserInfo tick_parser_info;
    NewTickParserInfo new_tick_parser_info;
    json json_info;
};
#endif //TICKINFOPARSER_H
