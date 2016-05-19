#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "MegaMan.h"

class Player {
    private:
        const std::string name;
        MegaMan megaman;

    public:
        explicit Player(const std::string& name);
        virtual ~Player();
};

#endif  // PLAYER_H
