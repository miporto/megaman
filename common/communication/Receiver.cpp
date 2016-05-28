#include <iostream>
#include "Receiver.h"

Receiver::Receiver(Socket& socket,
                   ReceivedPacketsProtected& packets)
        : socket(socket), packets(packets), quit(false) {}

void Receiver::run() {
    char packet_id = 0;
    while (!this->quit) {
        try {
            std::cout << "Receiving" << std::endl;
            this->socket.receive(&packet_id, sizeof(char));
        }
        catch (const SocketError& e) {
            std::cout << e.what() << std::endl;
            continue;
        }
        this->receive_packet(packet_id);
    }
}

void Receiver::shutdown() {
    this->quit = true;
}

Receiver::~Receiver() {
    this->shutdown();
    this->join();
}
