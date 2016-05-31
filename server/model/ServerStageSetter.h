#ifndef SERVERSTAGESETTER_H
#define SERVERSTAGESETTER_H

#include <vector>
#include <string>

#include "Enemy.h"
#include "Object.h"
#include "Map.h"
#include "common/StageParser.h"

class ServerStageSetter {
    private:
        std::vector<Enemy*> enemies;
        std::vector<Object*> objects;

        void to_classes(StageParserInfo& positions, Map* map);

    public:
        ServerStageSetter(const std::string& info, Map* map);
        ~ServerStageSetter();
};

#endif //SERVERSTAGESETTER_H
