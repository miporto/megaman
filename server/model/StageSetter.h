#ifndef SERVERSTAGESETTER_H
#define SERVERSTAGESETTER_H

#include <vector>
#include <string>

#include "Enemy.h"
#include "Object.h"
#include "Map.h"
#include "StageParser.h"

class StageSetter {
    private:
        void to_classes(StageParserInfo& positions, Map* map);

    public:
        StageSetter(const std::string& info, Map* map);
        ~StageSetter();
};

#endif //SERVERSTAGESETTER_H
