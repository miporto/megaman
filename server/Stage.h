#ifndef STAGE_H
#define STAGE_H

#include <vector>

#include "common/Thread.h"
#include "Player.h"
#include "Packet.h"

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

    public:
        StageFactory(char id);
        std::vector<char> positions_of_spawns(const int screen, const int enemy_id);
        std::vector<char> positions_of_objects(const int screen, const int object_id);
        ~StageFactory();
};

class Stage {
    private:
        StageFactory factory;
        std::vector<Player*>& players;
        int current_screen;

    public:
        Stage(char id, std::vector<Player*>& players);
        std::vector<StageInfo*> next_screen();
        ~Stage();
};

#endif //STAGE_H
