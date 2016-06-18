#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "Client.h"
#include "common/communication/AddrInfo.h"

Client::Client(const char* hostname, const char* port)
        : player_name("."), hostname(hostname), port(port),
          communicator(this->client, this->teammates) {}
        
void Client::connect_to_server() {
    struct addrinfo* ptr;
    bool connected = false;
    ClientAddrInfo info(this->hostname, this->port);

    for (ptr = info(); ptr != NULL && !connected; ptr = ptr->ai_next) {
        this->client(ptr);
        try {
            this->client.connect(ptr);
        }
        catch (const SocketError& e) {
            if (ptr->ai_next)
                continue;
            else
                throw;
        }
        connected = true;
    }
}

void Client::send_name(std::string& name) {
    player_name = name;
    this->communicator.send_name(name);
}

std::vector<std::string> Client::get_teammates() {
    return teammates;
}

void Client::pick_stage(char stage_id) {
    this->communicator.send_stage_pick(stage_id);
}

void Client::send_action(const char action_id, const bool pressed) {
    this->communicator.send_action(player_name, action_id, pressed);
}

char Client::receive_stage_id() {
    return communicator.receive_stage_id();
}

std::string Client::receive_stage_info() {
    std::string stage_info = this->communicator.receive_stage_info();
    while (stage_info.empty()) {
        stage_info = this->communicator.receive_stage_info();
    }
    return stage_info;
}

int Client::receive_deceased() {
    return communicator.receive_deceased();
}

UpdatePacket Client::receive_update() {
    return communicator.receive_update();
}

std::string Client::receive_chamber_info() {
    return communicator.receive_chamber_info();
}

bool Client::new_stage_id() {
    return communicator.new_stage_id();
}

bool Client::new_deceased() {
    return communicator.new_deceased();
}

bool Client::new_update_packets() {
    return communicator.new_update_packets();
}


bool Client::new_chamber_info_packet() {
    return communicator.new_chamber_info_packet();
}
Client::~Client() { this->client.shutdown(); }
