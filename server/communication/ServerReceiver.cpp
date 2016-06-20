#include <iostream>
#include "ServerReceiver.h"

ServerReceiver::ServerReceiver(Socket* socket,
                               ReceivedPacketsProtected& packets,
                               EventQueue& events)
        : Receiver(socket, packets), events(events) {}

void ServerReceiver::receive_packet(const char id) {
    Receiver::receive_packet(id);
    if (id == ACTION) {
        int length;
        this->socket->receive((char *) &length, sizeof(int));
        char *name = new char[length + 1];
        name[length] = '\0';
        this->socket->receive(name, sizeof(char) * length);
        char action_id, pressed;
        this->socket->receive(&action_id, sizeof(char));
        this->socket->receive(&pressed, sizeof(char));
        this->events.push(new Action(name, action_id, pressed));
        delete[] name;
    } else {
        std::cout << "RECVR Unknown packet id " << std::endl;
        //throw ReceiverError("Unknown packet id");
    }
}

ServerReceiver::~ServerReceiver() {}
