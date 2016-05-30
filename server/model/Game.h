#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "common/Thread.h"
#include "server/communication/Match.h"
#include "Player.h"
#include "Map.h"
#include "server/communication/EventQueue.h"

class Match;

class Game : public Thread {
    private:
        bool running;
        Match* match;
        Map map;
        EventQueue* events;

        void execute_events();
        void tick();
        void get_rid_of_corpses();
        const std::string status();

    public:
        explicit Game(Match* match);
        void new_player(Player* player);
        void set_event_queue
                (const std::vector<PacketsQueueProtected*>&action_queues);
        void set_stage(const std::string& info);
        void run();
        void quit();
        ~Game();
};

#endif //GAME_H
