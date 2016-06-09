#include <string>
#include <vector>
#include <iostream>
#include <utility>

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
          sender(&socket, this->packets_to_send),
          receiver(&socket, this->packets_received),
          waiter(teammates, this->packets_received) {}

void ClientCommunicator::send_name(std::string& name) {
    this->packets_to_send.push(new NewPlayer(name));
    this->receiver.start();
    this->waiter.start();
    this->sender.start();
}

void ClientCommunicator::send_stage_pick(char& stage_id) {
    this->packets_to_send.push(new StagePick(stage_id));
}

const std::string ClientCommunicator::receive_stage_info() {
    if (!this->packets_received.is_empty(STAGE_INFO)) {
        StageInfo* stage = (StageInfo*)this->packets_received.pop(STAGE_INFO);
        std::string info = stage->get_info();
        delete stage;
        return info;
    }
    // TODO: what to do if no stage info is received
    return "";
}

UpdatePacket ClientCommunicator::receive_update() {
    if (new_update_packets()) {
        Update* update = (Update*) packets_received.pop(UPDATE);
        std::string name = update->get_name();
        std::string update_info = update->get_update_info();
        delete update;
        return (UpdatePacket (name, update_info));
    }
    throw "ERROR: No update on queue!";
}

int ClientCommunicator::receive_deceased() {
    if (new_deceased()) {
        Deceased* update = (Deceased*) packets_received.pop(DECEASED);
        int id = update->get_id();
        delete update;
        return id;
    }
    throw "ERROR: No id on queue!";
}

void ClientCommunicator::send_action(const std::string& name,
                                     const char &action_id,
                                     const bool& pressed) {
    this->packets_to_send.push(new Action(name, action_id, pressed));
}

bool ClientCommunicator::new_update_packets() {
    return !packets_received.is_empty(UPDATE);
}

bool ClientCommunicator::new_deceased() {
    return !packets_received.is_empty(DECEASED);
}
ClientCommunicator::~ClientCommunicator() {
    this->waiter.join();
}
