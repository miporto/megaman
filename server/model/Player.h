#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "MegaMan.h"

class Player {
    private:
        std::string name;
        MegaMan megaman;

    public:
        void set_name(const std::string& name);
        const std::string& get_name();
        bool is_dead();
        const std::vector<int> get_position();
        int get_energy();
        virtual ~Player();
};

#endif  // PLAYER_H
