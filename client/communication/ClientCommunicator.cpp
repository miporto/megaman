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

NewUpdatePacket ClientCommunicator::receive_float_update() {
    NewUpdatePacket update_pkt;
    FloatUpdatePkt info;
    if (new_float_update_packets()) {
        const FloatUpdate *update = (FloatUpdate*) packets_received.pop
                (FLOAT_UPDATE);
        info["id"] = update->get_id();
        info["x"] = update->get_x();
        info["y"] = update->get_y();
        update_pkt.first = update->get_name();
        delete update;
    } else if (new_megaman_update_packets()){
        const MegaManFloatUpdate *update = (MegaManFloatUpdate*)
                packets_received.pop(MEGAMAN_FLOAT_UPDATE);
        info["id"] = update->get_id();
        info["x"] = update->get_x();
        info["y"] = update->get_y();
        info["d_x"] = update->get_direction_x();
        info["d_y"] = update->get_direction_y();
        update_pkt.first = update->get_name();
        delete update;
    } else {
        throw "ERROR: No float update on queue!";
    }
    update_pkt.second = info;
    return update_pkt;
}

NewUpdatePacket ClientCommunicator::receive_megaman_update() {
    NewUpdatePacket update_pkt;
    FloatUpdatePkt info;
    if (new_megaman_update_packets()) {
        const MegaManFloatUpdate *update = (MegaManFloatUpdate*)
                packets_received.pop(MEGAMAN_FLOAT_UPDATE);
        info["id"] = update->get_id();
        info["x"] = update->get_x();
        info["y"] = update->get_y();
        info["d_x"] = update->get_direction_x();
        info["d_y"] = update->get_direction_y();
        update_pkt.first = update->get_name();
        update_pkt.second = info;
        delete update;
        return update_pkt;
    }
    throw "ERROR: No megaman update on queue!";
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

bool ClientCommunicator::new_float_update_packets() {
    return !packets_received.is_empty(FLOAT_UPDATE) ||
            !packets_received.is_empty(MEGAMAN_FLOAT_UPDATE);
}

bool ClientCommunicator::new_megaman_update_packets() {
    return !packets_received.is_empty(MEGAMAN_FLOAT_UPDATE);
}

ClientCommunicator::~ClientCommunicator() {
    this->waiter.join();
}
