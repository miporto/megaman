#include <string>
#include <iostream>

#include "Sender.h"

Sender::Sender(SocketProtected& socket,
               PacketsProtected& packets,
               QuitProtected& quit)
        : socket(socket), packets(packets), quit(quit) {}

void Sender::run() {
    Packet* packet;
    std::string str;
    while (!this->quit()) {
        if (!this->packets.is_empty()) {
            packet = this->packets.pop();
            str = packet->get_str();
            str.push_back('\n');
            try {
                std::cout << "Sending" << std::endl;
                this->socket.send(str.c_str(), sizeof(char) * str.size());
            }
            catch (const SocketError &e) {
                std::cout << e.what() << std::endl;
                continue;
            }
            delete packet;
        }
    }
}

Sender::~Sender() {}
