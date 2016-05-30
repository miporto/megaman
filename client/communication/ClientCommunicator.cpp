#include <string>
#include <vector>
#include <iostream>

#include "ClientCommunicator.h"

TeamWaiter::TeamWaiter(std::vector<std::string>& teammates,
                       ReceivedPacketsProtected& packets_received) :
        teammates(teammates), packets_received(packets_received) {}

void TeamWaiter::run() {
    while (this->packets_received.is_empty(STAGE_PICK)) {
        if (!this->packets_received.is_empty(NEW_PLAYER)) {
            NewPlayer* packet = (NewPlayer*)this->packets_received
                    .pop(NEW_PLAYER);
            std::cout << "Teammate: " << packet->get_name() << std::endl;
            this->teammates.push_back(packet->get_name());
            delete packet;
        }
    }
}

TeamWaiter::~TeamWaiter() {}

ClientCommunicator::ClientCommunicator
        (Socket& socket, std::vector<std::string>& teammates)
        : socket(socket),
          receiver(socket, this->packets_received),
          waiter(teammates, this->packets_received) {}

void ClientCommunicator::push_to_sender(Packet* packet) {
    this->packets_to_send.push(packet);
    Sender s(this->socket, this->packets_to_send);
}

void ClientCommunicator::send_name(std::string& name) {
    this->push_to_sender(new NewPlayer(name));
    this->receiver.start();
    this->waiter.start();
}

void ClientCommunicator::send_stage_pick(char& stage_id) {
    this->push_to_sender(new StagePick(stage_id));
}

const std::string ClientCommunicator::receive_stage_info() {
    //TODO Completar
    return NULL;
}

void ClientCommunicator::send_action(char &action_id, bool pressed) {
    return;
}

ClientCommunicator::~ClientCommunicator() {
    this->waiter.join();
}
