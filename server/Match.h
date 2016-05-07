#ifndef MATCH_H
#define MATCH_H

#include <vector>

#include "common/Socket.h"
#include "Communicator.h"

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
        std::vector<Communicator>& communicators;
        std::vector<Player*> players;

    public:
        explicit Match(std::vector<Communicator>& communicators);
        bool has_host();
        Host* host();
        bool host_waiting();
        void add_player(int fd);
        ~Match();
};

#endif //MATCH_H
