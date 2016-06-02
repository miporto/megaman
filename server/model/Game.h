#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "common/Thread.h"
#include "server/communication/Match.h"
#include "MegaMan.h"
#include "Map.h"
#include "server/communication/EventQueue.h"

class Match;

class Game : public Thread {
    private:
        bool running;
        Match* match;
        Map map;
        EventQueue* events;
        std::vector<MegaMan*> players;

        void execute_events();
        void execute_action(MegaMan* player,
                            const char action_id, const bool pressed);
        void tick();
        void check_collisions();
        void get_rid_of_corpses();
        const std::string status();
        MegaMan* player_with_name(const std::string& name);

    public:
        explicit Game(Match* match);
        void new_player(MegaMan* player);
        void set_event_queue
                (const std::vector<PacketsQueueProtected*>& action_queues);
        void set_stage(const std::string& info);
        void run();
        void quit();
        ~Game();
};

#endif //GAME_H
