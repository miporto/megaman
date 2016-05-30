#include <iostream>
#include <string>

#include "Client.h"
#include "common/communication/AddrInfo.h"

Client::Client(const char* hostname, const char* port)
        : hostname(hostname), port(port),
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
    this->communicator.send_name(name);
}

void Client::pick_stage(char stage_id) {
    this->communicator.send_stage_pick(stage_id);
}

void Client::send_action(char action_id, bool pressed) {
    return;
}
Client::~Client() { this->client.shutdown(); }
