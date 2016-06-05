#ifndef MATCH_H
#define MATCH_H

#include <string>
#include <vector>
#include <map>

#include "common/SystemError.h"
#include "common/communication/Socket.h"
#include "ServerCommunicator.h"
#include "server/model/Game.h"
#include "Stage.h"

class Game;
class Match {
    private:
        Mutex m;
        std::vector<ServerCommunicator*>& communicators;
        Game game;

        bool has_host();
        HostCommunicator* host_communicator();
        void notify_team_to_new_player(ServerCommunicator* new_comm);
        void notify_new_player_to_team(ServerCommunicator* new_comm);
        void notify_stage_pick_to_team(const char stage_id);
        void notify_stage_info(const std::string& info);
        void set_game(const std::string& stage_info);

    public:
        explicit Match(std::vector<ServerCommunicator*>& communicators);
        bool has_started();
        bool is_full();
        void add_player(Socket* peer);
        void start_stage();
        void notify_tick(const std::string& tick_info);
        ~Match();
};

class MatchError : public SystemError {
    public:
        explicit MatchError(const std::string error_msg) throw();
};

#endif  // MATCH_H
