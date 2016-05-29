#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "common/Thread.h"
#include "server/communication/Match.h"
#include "Player.h"
#include "Map.h"

class Match;

class Game : public Thread {
    private:
        Match* match;
        Map map;

        void tick();
        void get_rid_of_corpses();
        const std::string status();

    public:
        explicit Game(Match* match);
        void new_player(Player* player);
        void set_stage(const std::string& info);
        void run();
        ~Game();
};

#endif //GAME_H
