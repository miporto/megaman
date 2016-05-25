#include <iostream>
#include "Receiver.h"

Receiver::Receiver(Socket& socket,
                   PacketsProtected& packets,
                   QuitProtected& quit)
        : socket(socket), packets(packets), quit(quit) {}

void Receiver::run() {
    char packet_id = 0;
    while (!this->quit() && packet_id != '\n') {
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

Receiver::~Receiver() {}
