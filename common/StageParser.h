#ifndef STAGEPARSER_H
#define STAGEPARSER_H

#include <string>
#include <vector>
#include <map>

typedef std::vector<std::vector<int>> StageParserPositions;
typedef std::map<std::string, std::vector<std::vector<int>>> StageParserInfo;

class StageParser {
    private:
        StageParserPositions positions_of(const std::string& info,
                                          const std::string& name,
                                          const std::string& object_name);
    public:
        StageParserInfo stage_info(const std::string& info);
        ~StageParser();
};


#endif //STAGEPARSER_H
