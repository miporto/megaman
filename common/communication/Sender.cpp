#include <string>
#include <iostream>

#include "Sender.h"

Sender::Sender(Socket* socket,
               PacketsQueueProtected& packets)
        : socket(socket), packets(packets), quit(false) {}

void Sender::run() {
    Packet* packet;
    std::string str;
    while (!this->quit) {
        if (!this->packets.is_empty()) {
            packet = this->packets.pop();
            str = packet->get_str();
            try {
                this->socket->send(str.c_str(), sizeof(char) * str.size());
            }
            catch (const SocketError &e) {
                delete packet;
                break;
            }
            delete packet;
        }
    }
}

void Sender::shutdown() {
    this->quit = true;
}

Sender::~Sender() {
    this->shutdown();
    this->join();
}
