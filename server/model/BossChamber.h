#ifndef BOSSCHAMBER_H
#define BOSSCHAMBER_H

#include <string>
#include <vector>
#include <map>

#include "server/communication/EventQueue.h"
#include "Player.h"
#include "Boss.h"

class ServerCommunicator;
class Match;

class BossChamber {
    private:
        Match* match;
        Boss* boss;
        std::vector<Player*> players;
        EventQueue* events;

        std::vector<GameObject*> objects;
        std::map<GameObject*, int> object_id;

        void execute_events();
        void execute_action(Player* player,
                            const char action_id, const bool pressed);
        void tick();
        void check_collisions();
        void get_rid_of_corpses();
        void create_new_projectiles();
        void collect_updates();
        Player* player_with_name(const std::string& name);
        bool players_are_dead();
        const std::string status();

    public:
        BossChamber(Match* match,
                    std::vector<ServerCommunicator*>& communicators,
                    const char boss_id);
        void add_game_object(GameObject* object);
        void run(bool* exit);
        bool beated();
        ~BossChamber();
};

class BossChamberError : public SystemError {
public:
    explicit BossChamberError(const std::string error_msg) throw();
};

#endif //BOSSCHAMBER_H
