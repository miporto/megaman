#ifndef TICKINFOPARSER_H
#define TICKINFOPARSER_H

#include <map>
#include <string>
#include <vector>

#include "extern/libjson/json.hpp"

using json = nlohmann::json;

typedef std::map<int, std::map<std::string, std::string>> StatusInfo;
typedef std::map<std::string, StatusInfo> TickParserInfo;

class TickInfoParser {
public:
    explicit TickInfoParser(const std::string& tick_info);
    TickParserInfo get_parsed_tick_info();
    static std::map<std::string, std::string> parse_update(
            const std::string &info);
    ~TickInfoParser();
private:
    StatusInfo status_info_of(const std::string& element);
    std::string tick_info;
    TickParserInfo new_tick_parser_info;
    json json_info;
};
#endif //TICKINFOPARSER_H
