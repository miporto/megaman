#ifndef MATCH_H
#define MATCH_H

#include <string>
#include <vector>
#include <map>

#include "common/communication/Socket.h"
#include "ServerCommunicator.h"
#include "server/model/Game.h"
#include "server/model/Player.h"
#include "Stage.h"

class Match {
    private:
        Mutex m;
        std::vector<ServerCommunicator*>& communicators;
        std::map<char, StageInfo*> stages;
        Game game;

        bool has_host();
        HostCommunicator* host_communicator();
        void send_team_to_new_player(ServerCommunicator* new_comm);
        void send_new_player_to_team(ServerCommunicator* new_comm);
        void send_stage_pick_to_team(const char stage_id);
        void send_stage_info(StageInfo* info);

    public:
        explicit Match(std::vector<ServerCommunicator*>& communicators);
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
