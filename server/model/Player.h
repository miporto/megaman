#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "MegaMan.h"

class Player {
    private:
        std::string name;
        MegaMan* megaman;
        std::vector<std::string> ammo_rewards;

    public:
        Player();
        void set_name(const std::string& name);
        std::string& get_name();
        void new_megaman();
        MegaMan* get_megaman();
        bool alive();
        void add_reward(const std::string& ammo_name);
        ~Player();
};


#endif //PLAYER_H
