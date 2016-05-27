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

StageInfo* ClientCommunicator::receive_stage_info() {
    std::vector<Position*> met_positions;
    std::vector<Position*> bumby_positions;
    std::vector<Position*> sniper_positions;
    std::vector<Position*> jumping_sniper_positions;
    std::vector<Position*> block_positions;
    std::vector<Position*> stairs_positions;
    std::vector<Position*> spike_positions;
    std::vector<Position*> cliff_positions;

    //TODO Ver que llegue completo (Hacer unico paquete con todo)
    while (!this->packets_received.is_empty(STAGE_ELEMENT)) {
        StageElement* packet = (StageElement*)
                this->packets_received.pop(STAGE_ELEMENT);
        switch (packet->get_type()) {
            case MET:
                met_positions.push_back(packet->get_position());
                break;
            case BUMBY:
                bumby_positions.push_back(packet->get_position());
                break;
            case SNIPER:
                sniper_positions.push_back(packet->get_position());
                break;
            case JUMPING_SNIPER:
                jumping_sniper_positions.push_back(packet->get_position());
                break;
            case BLOCK:
                block_positions.push_back(packet->get_position());
                break;
            case STAIRS:
                stairs_positions.push_back(packet->get_position());
                break;
            case SPIKE:
                spike_positions.push_back(packet->get_position());
                break;
            case CLIFF:
                cliff_positions.push_back(packet->get_position());
                break;
            default:
                break;
        }
        delete packet;
    }

    return new StageInfo(met_positions,
                          bumby_positions,
                          sniper_positions,
                          jumping_sniper_positions,
                          block_positions,
                          stairs_positions,
                          spike_positions,
                         cliff_positions);
}

ClientCommunicator::~ClientCommunicator() {
    this->waiter.join();
}
