#ifndef STAGE_H
#define STAGE_H

#include <vector>
#include <common/StageInfo.h>

#include "common/Thread.h"
#include "Player.h"
#include "common/Packet.h"
#include "Object.h"
#include "Enemy.h"

class StageIDProtected {
    private:
        Mutex m;
        char stage_id;

    public:
        StageIDProtected();
        void set_id(char stage_id);
        char operator()();
        ~StageIDProtected();
};

class StageFactory {
    private:
        std::vector<char> positions_of_spawns
                (const int stage_id, const int enemy_id);
        std::vector<char> positions_of_objects
                (const int stage_id, const int object_id);

    public:
        StageInfo* operator()(const int stage_id);
        ~StageFactory();
};

class Stage {
    private:
        const int id;
        std::vector<Player*>& players;
        std::vector<Enemy*> enemies;
        std::vector<Object*> objects;

    public:
        Stage(char id, std::vector<Player*>& players);
        StageInfo* get_stage_info();
        ~Stage();
};

#endif  // STAGE_H
