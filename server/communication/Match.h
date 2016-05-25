#ifndef MATCH_H
#define MATCH_H

#include <string>
#include <vector>


#include "common/communication/Socket.h"
#include "ServerCommunicator.h"
#include "server/model/Game.h"
#include "server/model/Player.h"
#include "Stage.h"

class Match {
    private:
        Mutex m;
        std::vector<ServerCommunicator*>& communicators;
        Game game;
        StageIDProtected stage_id;

        bool has_host();
        //Match realiza envio de informacion cuando esta se debe mandar a todos
        // los jugadores por igual
        void send_new_player_notification(std::string& name);
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
