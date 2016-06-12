#include <exception>
#include <iostream>
#include <string>

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

/*
 * A partir de aca; metodos para todas las decisiones que toma el jugador
 * que requieren un envio de informacion el server
 */

void Client::send_name(std::string& name) {
    player_name = name;
    this->communicator.send_name(name);
}

void Client::pick_stage(char stage_id) {
    this->communicator.send_stage_pick(stage_id);
}

void Client::send_action(const char action_id, const bool pressed) {
    // TODO: send the players name to the communicator
    this->communicator.send_action(player_name, action_id, pressed);
}

std::string Client::receive_stage_info() {
    std::string stage_info = this->communicator.receive_stage_info();
    while (stage_info.empty()) {
        stage_info = this->communicator.receive_stage_info();
    }
    return stage_info;
}

UpdatePacket Client::receive_update() {
    return communicator.receive_update();
}

int Client::receive_deceased() {
    return communicator.receive_deceased();
}

NewUpdatePacket Client::receive_float_update() {
    return communicator.receive_float_update();
}

NewUpdatePacket Client::receive_megaman_update() {
    return communicator.receive_megaman_update();
}

bool Client::new_update_packets() {
    return communicator.new_update_packets();
}

bool Client::new_deceased() {
    return communicator.new_deceased();
}

bool Client::new_float_update_packets() {
    return communicator.new_float_update_packets();
}

bool Client::new_megaman_update_packets() {
    return communicator.new_megaman_update_packets();
}
Client::~Client() { this->client.shutdown(); }
