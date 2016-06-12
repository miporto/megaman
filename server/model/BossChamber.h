#ifndef BOSSCHAMBER_H
#define BOSSCHAMBER_H

#include <string>
#include <vector>

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
        std::vector<Projectile*> projectiles;
        EventQueue* events;

        void execute_events();
        void execute_action(Player* player,
                            const char action_id, const bool pressed);
        void add_projectile(Projectile* projectile);
        Player* player_with_name(const std::string& name);
        bool players_are_dead();

    public:
        BossChamber(Match* match,
                    std::vector<ServerCommunicator*>& communicators,
                    const char boss_id);
        void run(bool* exit);
        bool beated();
        ~BossChamber();
};

class BossChamberError : public SystemError {
public:
    explicit BossChamberError(const std::string error_msg) throw();
};

#endif //BOSSCHAMBER_H
