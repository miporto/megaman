#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "common/StageInfo.h"
#include "Player.h"
#include "Map.h"

class Game {
    private:
        std::vector<Player*> players;
        Map map;

    public:
        void new_player(std::string& name);
        void start_stage(StageInfo* info);
        ~Game();
};

#endif //GAME_H
