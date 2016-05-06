#ifndef MATCH_H
#define MATCH_H

#include <vector>

#include "common/Socket.h"

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
        bool waiting_for_players();
        ~Host();
};

class Match {
    private:
        std::vector<Player*> players;

    public:
        Host* host();
        bool host_waiting();
        void add_player(int fd);
        ~Match();
};

#endif //MATCH_H
