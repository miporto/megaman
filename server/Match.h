#ifndef MATCH_H
#define MATCH_H

#include <vector>

#include "common/Socket.h"
#include "Communicator.h"

class Player {
    private:

    public:
        virtual ~Player();
};

// Ver si tiene sentido esta clase
class Host : public Player {
    public:
        ~Host();
};

class Match {
    private:
        std::vector<Communicator*>& communicators;
        std::vector<Player*> players;

        bool has_host();
        void new_player_notification();

    public:
        explicit Match(std::vector<Communicator*>& communicators);
        bool started();
        void add_player(int fd);
        ~Match();
};

#endif //MATCH_H
