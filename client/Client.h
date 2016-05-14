#ifndef MEGAMAN_CLIENT_H
#define MEGAMAN_CLIENT_H

#include <string>

#include "common/Socket.h"
#include "ClientCommunicator.h"

class Client {
    private:
        SocketProtected& client;
        ClientCommunicator communicator;

        void connect_to_server(const char* hostname, const char* port);

    public:
        Client(SocketProtected& client, const char* hostname, const char* port);
        void send_name(std::string& name);
        void pick_stage(char& stage_id);
        ~Client();
};

#endif  // MEGAMAN_CLIENT_H
