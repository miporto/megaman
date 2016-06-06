#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "MegaMan.h"

class Player {
    private:
        std::string name;
        MegaMan* megaman;

    public:
        Player();
        void set_name(const std::string& name);
        std::string& get_name();
        void new_megaman();
        MegaMan* get_megaman();
        bool alive();
        ~Player();
};


#endif //PLAYER_H
