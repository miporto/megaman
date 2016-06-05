#include <iostream>
#include "Receiver.h"

Receiver::Receiver(Socket* socket,
                   ReceivedPacketsProtected& packets)
        : socket(socket), packets(packets), started(false), quit(false) {}

void Receiver::start() {
    this->started = true;
    Thread::start();
}

void Receiver::receive_packet(const char id) {
    switch (id) {
        case NEW_PLAYER: {
            int length;
            this->socket->receive((char*)&length, sizeof(int));
            char* name = new char[length];
            this->socket->receive(name, sizeof(char) * length);
            this->packets.push(new NewPlayer(name));
            delete name;
            break;
        } case STAGE_PICK: {
            char stage_id;
            this->socket->receive(&stage_id, sizeof(char));
            this->packets.push(new StagePick(stage_id));
            break;
        } case STAGE: {
            int length;
            this->socket->receive((char*)&length, sizeof(int));
            char* info = new char[length];
            this->socket->receive(info, sizeof(char) * length);
            this->packets.push(new Stage(info));
            delete info; // Stage supuestamente lo copia, pero hay que probar
            // que no desaparezca despues de esto c:
            break;
        } case ACTION: {
            int length;
            this->socket->receive((char*)&length, sizeof(int));
            char* name = new char[length];
            this->socket->receive(name, sizeof(char) * length);
            char action_id, pressed;
            this->socket->receive(&action_id, sizeof(char));
            this->socket->receive(&pressed, sizeof(char));
            this->packets.push(new Action(name, action_id, pressed));
            delete name;
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
            this->socket->receive(&packet_id, sizeof(char));
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
    if (started) this->join();
}
