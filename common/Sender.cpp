#include <string>
#include <iostream>

#include "Sender.h"

#define END_OF_MESSAGE '\n'

Sender::Sender(Socket& socket,
               PacketsProtected& packets,
               QuitProtected& quit)
        : socket(socket), packets(packets), quit(quit) {
    this->start();
}

void Sender::run() {
    Packet* packet;
    std::string str;
    while (!this->quit() && !this->packets.is_empty()) {
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

    if (!this->quit()) {
        char EOM = END_OF_MESSAGE;
        this->socket.send(&EOM, sizeof(char));
    }
}

Sender::~Sender() {
    this->join();
}
