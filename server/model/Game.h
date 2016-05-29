#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <common/Thread.h>

#include "common/communication/StageInfo.h"
#include "Player.h"
#include "Map.h"

class Game {
    private:
        std::vector<Player*> players;
        Map map;

        void get_rid_of_corpses();

    public:
        void new_player(Player* player);
        void set_stage(const char stage_id);
        void tick();
        ~Game();
};

#endif //GAME_H
