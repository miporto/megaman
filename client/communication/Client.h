#ifndef MEGAMAN_CLIENT_H
#define MEGAMAN_CLIENT_H

#include <string>
#include <vector>

#include "common/communication/Socket.h"
#include "ClientCommunicator.h"

class Client {
    private:
		const char* hostname;
		const char* port;
        Socket client;
        ClientCommunicator communicator;
		std::vector<std::string> teammates;

    public:
        Client(const char* hostname, const char* port);
        void connect_to_server();
        void send_name(std::string& name);
        void pick_stage(char stage_id);
        ~Client();
};

#endif  // MEGAMAN_CLIENT_H
