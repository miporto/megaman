#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
    private:
        const std::string name;

    public:
        explicit Player(const std::string& name);
        virtual ~Player();
};

#endif  // PLAYER_H
