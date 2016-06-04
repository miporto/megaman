#ifndef TICKINFOPARSER_H
#define TICKINFOPARSER_H

#include <map>
#include <string>
#include <vector>

typedef std::vector<std::vector<int>> Coordinates;
typedef std::map<std::string, Coordinates> TickParserInfo;

class TickInfoParser {
public:
    explicit TickInfoParser(const std::string& tick_info);
    TickParserInfo get_parsed_tick_info();
    ~TickInfoParser();
private:
    Coordinates coordinates_of(const std::string& actor);
    std::string tick_info;
    TickParserInfo tick_parser_info;
};

#endif //TICKINFOPARSER_H
