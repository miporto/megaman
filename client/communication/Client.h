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
        void pick_stage(char stage_id);
		void send_action(const char action_id, const bool pressed);
		std::string receive_stage_info();
        UpdatePacket receive_update();
        int receive_deceased();
        NewUpdatePacket receive_float_update();
        NewUpdatePacket receive_megaman_update();
        std::string receive_chamber_info();
	    bool new_update_packets();
	    bool new_deceased();
        bool new_float_update_packets();
        bool new_megaman_update_packets();
        bool new_chamber_info_packet();
        ~Client();
};

#endif  // MEGAMAN_CLIENT_H
