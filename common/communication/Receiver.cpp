#include <iostream>
#include "Receiver.h"

Receiver::Receiver(Socket& socket,
                   ReceivedPacketsProtected& packets)
        : socket(socket), packets(packets), quit(false) {}

void Receiver::receive_packet(const char id) {
    switch (id) {
        case NEW_PLAYER: {
            char name[NAME_LENGTH + 1];
            name[NAME_LENGTH] = '\0';
            this->socket.receive(name, sizeof(char) * NAME_LENGTH);
            this->packets.push(new NewPlayer(name));
            break;
        } case STAGE_PICK: {
            char stage_id;
            this->socket.receive(&stage_id, sizeof(char));
            this->packets.push(new StagePick(stage_id));
            break;
        } case STAGE: {
            char info[INFO_LENGTH];
            this->socket.receive((char *) &info,
                                 sizeof(char) * INFO_LENGTH);
            this->packets.push(new Stage(info));
            break;
        } default:
            // Si el ID es desconocido, es posible que el resto del
            // paquete quede en el pipe del socket, arruinando la comm
            break;
    }
}

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
