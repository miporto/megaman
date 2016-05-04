#ifndef MATCH_H
#define MATCH_H

#include <vector>

#include "commonSocket.h"

class Player {
    private:
        Socket peer;

    public:
        Player(int fd);
        virtual ~Player();
};

class Host : public Player {
    public:
        Host(int fd);
        ~Host();
};

class Match {
    private:
        std::vector<Player*> players;

    public:
        Host* host();
        void add_player(int fd);
        ~Match();
};

#endif //MATCH_H
