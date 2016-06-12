#ifndef STAGE_H
#define STAGE_H

#include <vector>
#include <string>

#include "common/SystemError.h"
#include "Player.h"
#include "Map.h"
#include "server/communication/EventQueue.h"

class ServerCommunicator;
class Match;

class Stage {
    private:
        Match* match;
        std::vector<Player*> players;
        Map map;
        EventQueue* events;
        bool end_reached;

        void execute_events();
        void execute_action(Player* player,
                            const char action_id, const bool pressed);
        void tick();
        void check_collisions();
        void acknowledge_deceased();
        void create_new_projectiles();
        void acknowledge_updates();
        Player* player_with_name(const std::string& name);
        bool players_are_dead();

    public:
        Stage(Match* match,
              std::vector<ServerCommunicator*>& communicators,
              const std::string& stage_info);
        void run(bool* exit);
        bool beated();
        ~Stage();
};

class StageError : public SystemError {
public:
    explicit StageError(const std::string error_msg) throw();
};

#endif  // STAGE_H
