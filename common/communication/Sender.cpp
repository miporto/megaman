#include <string>
#include <iostream>

#include "Sender.h"

Sender::Sender(Socket& socket,
               PacketsQueueProtected& packets)
        : socket(socket), packets(packets) {
    this->start();
}

void Sender::run() {
    Packet* packet;
    std::string str;
    while (!this->packets.is_empty()) {
        packet = this->packets.pop();
        str = packet->get_str();
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

Sender::~Sender() {
    this->join();
}
