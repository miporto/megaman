#ifndef MEGAMAN_CLIENT_H
#define MEGAMAN_CLIENT_H

#include <string>
#include <vector>

#include "common/communication/Socket.h"
#include "ClientCommunicator.h"

class Client {
    private:
		std::string player_name;
		const char* hostname;
		const char* port;
        Socket client;
        ClientCommunicator communicator;
		std::vector<std::string> teammates;

    public:
        Client(const char* hostname, const char* port);
        void connect_to_server();
        void send_name(std::string& name);
		std::vector<std::string> get_teammates();
        void pick_stage(char stage_id);
		void send_action(const char action_id, const bool pressed);
        char receive_stage_id();
		std::string receive_stage_info();
        int receive_deceased();
        UpdatePacket receive_update();
        std::string receive_chamber_info();
        bool new_stage_id();
	    bool new_deceased();
        bool new_update_packets();
        bool new_chamber_info_packet();
        ~Client();
};

#endif  // MEGAMAN_CLIENT_H
