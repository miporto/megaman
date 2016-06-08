#ifndef MATCH_H
#define MATCH_H

#include <string>
#include <vector>
#include <map>

#include "common/SystemError.h"
#include "common/communication/Socket.h"
#include "ServerCommunicator.h"
#include "server/model/Stage.h"

class Match {
    private:
        std::map<char, std::string> stages;
        Mutex m;
        std::vector<ServerCommunicator*>& communicators;

        bool has_host();
        HostCommunicator* host_communicator();
        void notify_team_to_new_player(ServerCommunicator* new_comm);
        void notify_new_player_to_team(ServerCommunicator* new_comm);
        void notify_stage_pick_to_team(const char stage_id);

    public:
        explicit Match(std::vector<ServerCommunicator*>& communicators);
        bool has_started();
        bool is_full();
        bool ended();
        void add_player(Socket* peer);
        void play_stage();
        void notify_deceased(const int object_id);
        void notify_stage_info(const std::string& info);
        void notify_tick(const std::string& tick_info);
        ~Match();
};

class MatchError : public SystemError {
    public:
        explicit MatchError(const std::string error_msg) throw();
};

#endif  // MATCH_H
