#ifndef STAGE_H
#define STAGE_H

#include <vector>
#include <common/ScreenInfo.h>

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
        char id;

        std::vector<char> positions_of_spawns
                (const int screen, const int enemy_id);
        std::vector<char> positions_of_objects
                (const int screen, const int object_id);

    public:
        explicit StageFactory(char id);
        ScreenInfo* screen_info(const int screen);
        ~StageFactory();
};

class Stage {
    private:
        StageFactory factory;
        std::vector<Player*>& players;
        std::vector<Enemy*> enemies;
        std::vector<Object*> objects;
        int current_screen;

    public:
        Stage(char id, std::vector<Player*>& players);
        ScreenInfo* next_screen();
        ~Stage();
};

#endif  // STAGE_H
