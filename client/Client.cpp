#include <iostream>
#include <string>

#include "Client.h"
#include "common/AddrInfo.h"

//Se instancia una vez que el usuario clickeo START

void Client::connect_to_server(const char* hostname, const char* port) {
    struct addrinfo* ptr;
    bool connected = false;
    ClientAddrInfo info(hostname, port);

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

Client::Client(SocketProtected& client, const char* hostname, const char* port)
        : client(client), communicator(this->client) {
    this->connect_to_server(hostname, port);
}

/*
 * A partir de aca; metodos para todas las decisiones que toma el jugador
 * que requieren un envio de informacion el server
 */

void Client::send_name(std::string& name) {
    this->communicator.send_name(name);
}

void Client::pick_stage(char& stage_id) {
    this->communicator.send_stage_pick(stage_id);
}

Client::~Client() { this->client.shutdown(); }
