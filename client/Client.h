#ifndef MEGAMAN_CLIENT_H
#define MEGAMAN_CLIENT_H

#include <string>

#include "common/Socket.h"
#include "ClientCommunicator.h"

typedef enum _stage_id {
	BOMBMAN = 1,
	SPARKMAN,
	FIREMAN,
	RINGMAN,
	MAGNETMAN
} stage_id_t;

class Client {
    private:
		const char* hostname;
		const char* port;
        Socket client;
        ClientCommunicator communicator;

    public:
        Client(const char* hostname, const char* port);
        void connect_to_server();
        void send_name(std::string& name);
        void pick_stage(char stage_id);
        ~Client();
};

#endif  // MEGAMAN_CLIENT_H
