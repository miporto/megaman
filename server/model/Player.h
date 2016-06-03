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
        MegaMan* get_megaman();
        void new_megaman();
        ~Player();
};


#endif //PLAYER_H
