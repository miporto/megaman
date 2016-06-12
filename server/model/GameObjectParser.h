#ifndef STAGEPARSER_H
#define STAGEPARSER_H

#include <string>
#include <vector>
#include <map>

typedef std::vector<std::vector<float>> GameObjectParserPositions;
typedef std::map<std::string, std::vector<std::vector<float>>>
        GameObjectParserInfo;

class GameObjectParser {
    private:
        GameObjectParserPositions positions_of(const std::string& info,
                                               const std::string& name,
                                               const std::string& object_name);
    public:
        GameObjectParserInfo stage_info(const std::string& info);
        ~GameObjectParser();
};


#endif //STAGEPARSER_H
