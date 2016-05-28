#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "MegaMan.h"

class Player {
    private:
        std::string name;
        MegaMan megaman;

    public:
        void set_name(const std::string& name);
        const std::string& get_name();
        bool is_dead();
        virtual ~Player();
};

#endif  // PLAYER_H
