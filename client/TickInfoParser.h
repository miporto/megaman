#ifndef TICKINFOPARSER_H
#define TICKINFOPARSER_H

#include <map>
#include <string>
#include <vector>

class TickInfoParser {
public:
    explicit TickInfoParser(const std::string& tick_info);
    ~TickInfoParser();
private:
    typedef std::vector<std::vector<int>> Coordinates;
    typedef std::map<std::string, std::vector<Coordinates>> TickInfoMap;
};

#endif //TICKINFOPARSER_H
