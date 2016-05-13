#ifndef MATCH_H
#define MATCH_H

#include <string>
#include <vector>

#include "common/Socket.h"
#include "Communicator.h"
#include "Player.h"
#include "Stage.h"

class Match {
    private:
        Mutex m;
        std::vector<Communicator*>& communicators;
        std::vector<Player*> players;
        StageIDProtected stage_id;

        bool has_host();
        void new_player_notification(std::string& name);

    public:
        explicit Match(std::vector<Communicator*>& communicators);
        bool has_started();
        bool is_full();
        void add_player(int fd);
        void start_stage();
        ~Match();
};

class MatchError : public std::exception {
    private:
        const std::string error_msg;

    public:
        explicit MatchError(const std::string error_msg) throw();
        const char* what() const throw();
        ~MatchError() throw();
};

#endif  // MATCH_H
