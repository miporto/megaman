#include <string>
#include <vector>
#include <iostream>
#include <utility>

#include "ClientCommunicator.h"

TeamWaiter::TeamWaiter(std::vector<std::string> &teammates,
                       ReceivedPacketsProtected &packets_received) :
        teammates(teammates), packets_received(packets_received) { }

void TeamWaiter::run() {
    while (this->packets_received.is_empty(STAGE_PICK)) {
        if (!this->packets_received.is_empty(NEW_PLAYER)) {
            NewPlayer *packet = (NewPlayer *) this->packets_received
                    .pop(NEW_PLAYER);
            std::cout << "Teammate: " << packet->get_name() << std::endl;
            this->teammates.push_back(packet->get_name());
            delete packet;
        }
    }
}

TeamWaiter::~TeamWaiter() { }

ClientCommunicator::ClientCommunicator
        (Socket &socket, std::vector<std::string> &teammates)
        : socket(socket),
          sender(&socket, this->packets_to_send),
          receiver(&socket, this->packets_received),
          waiter(teammates, this->packets_received) { }

void ClientCommunicator::send_name(std::string &name) {
    this->packets_to_send.push(new NewPlayer(name));
    this->receiver.start();
    this->waiter.start();
    this->sender.start();
}

void ClientCommunicator::send_stage_pick(char &stage_id) {
    this->packets_to_send.push(new StagePick(stage_id));
}


void ClientCommunicator::send_action(const std::string &name,
                                     const char &action_id,
                                     const bool &pressed) {
    this->packets_to_send.push(new Action(name, action_id, pressed));
}

const std::string ClientCommunicator::receive_stage_info() {
    if (!this->packets_received.is_empty(STAGE_INFO)) {
        StageInfo *stage = (StageInfo *) this->packets_received.pop(STAGE_INFO);
        std::string info = stage->get_info();
        delete stage;
        return info;
    }
    // TODO: what to do if no stage info is received
    return "";
}

//UpdatePacket ClientCommunicator::receive_update() {
//    if (new_update_packets()) {
//        Update* update = (Update*) packets_received.pop(UPDATE);
//        std::string name = update->get_name();
//        std::string update_info = update->get_update_info();
//        delete update;
//        return (UpdatePacket (name, update_info));
//    }
//    throw "ERROR: No update on queue!";
//}

UpdatePacket ClientCommunicator::receive_update() {
    if (new_float_update_packets()) {
        return receive_float_update();
    } else if (new_megaman_update_packets()) {
        return receive_megaman_update();
    } else if (new_enemy_update()) {
        return receive_enemy_update();
    } else if (new_boss_update()) {
        return receive_boos_update();
    } else {
        throw "ERROR: no update packets";
    }
}

int ClientCommunicator::receive_deceased() {
    if (new_deceased()) {
        Deceased *update = (Deceased *) packets_received.pop(DECEASED);
        int id = update->get_object_id();
        delete update;
        return id;
    }
    throw "ERROR: No id on queue!";
}

UpdatePacket ClientCommunicator::receive_float_update() {
    UpdatePacket update_pkt;
    UpdateInfo info;
    const FloatUpdate *update = (FloatUpdate *) packets_received.pop
            (FLOAT_UPDATE);
    info["id"] = update->get_object_id();
    info["x"] = update->get_x();
    info["y"] = update->get_y();
    update_pkt.first = update->get_name();
    update_pkt.second = info;
    delete update;
    return update_pkt;
}

UpdatePacket ClientCommunicator::receive_megaman_update() {
    UpdatePacket update_pkt;
    UpdateInfo info;
    const MegaManFloatUpdate *update = (MegaManFloatUpdate *)
            packets_received.pop(MEGAMAN_FLOAT_UPDATE);
    info["id"] = update->get_object_id();
    info["x"] = update->get_x();
    info["y"] = update->get_y();
    info["dir_x"] = update->get_direction_x();
    info["dir_y"] = update->get_direction_y();
    info["energy"] = update->get_energy();
//    std::cout << info["energy"] << std::endl;
    update_pkt.first = update->get_name();
    update_pkt.second = info;
    delete update;
    return update_pkt;
}

UpdatePacket ClientCommunicator::receive_enemy_update() {
    UpdatePacket update_pkt;
    UpdateInfo info;
    EnemyFloatUpdate *update = (EnemyFloatUpdate *) packets_received.pop
            (ENEMY_FLOAT_UPDATE);
    info["id"] = update->get_object_id();
    info["x"] = update->get_x();
    info["y"] = update->get_y();
    info["covered"] = update->is_covered();
    update_pkt.first = update->get_name();
    update_pkt.second = info;
    delete update;
    return update_pkt;
}

UpdatePacket ClientCommunicator::receive_boos_update() {
    UpdatePacket update_pkt;
    UpdateInfo info;
    BossFloatUpdate *update = (BossFloatUpdate *) packets_received.pop
            (BOSS_FLOAT_UPDATE);
    info["id"] = update->get_object_id();
    info["x"] = update->get_x();
    info["y"] = update->get_y();
    info["dir_x"] = update->get_direction_x();
    info["dir_y"] = update->get_direction_y();
    info["energy"] = update->get_energy();
    update_pkt.first = update->get_name();
    update_pkt.second = info;
    delete update;
    return update_pkt;
}

std::string ClientCommunicator::receive_chamber_info() {
    std::string info;
    if (new_chamber_info_packet()) {
        const ChamberInfo *update = (ChamberInfo *) packets_received.pop
                (CHAMBER_INFO);
        info = update->get_info();
        delete update;
        return info;
    }
    throw "ERROR: No chamber info on queue!";
}

bool ClientCommunicator::new_stage_pick() {
    return !packets_received.is_empty(STAGE_PICK);
}
bool ClientCommunicator::new_update_packets() {
    return new_float_update_packets() || new_megaman_update_packets() ||
           new_enemy_update() || new_boss_update();
}

bool ClientCommunicator::new_deceased() {
    return !packets_received.is_empty(DECEASED);
}

bool ClientCommunicator::new_float_update_packets() {
    return !packets_received.is_empty(FLOAT_UPDATE);
}

bool ClientCommunicator::new_megaman_update_packets() {
    return !packets_received.is_empty(MEGAMAN_FLOAT_UPDATE);
}

bool ClientCommunicator::new_enemy_update() {
    return !packets_received.is_empty(ENEMY_FLOAT_UPDATE);
}

bool ClientCommunicator::new_boss_update() {
    return !packets_received.is_empty(BOSS_FLOAT_UPDATE);
}

bool ClientCommunicator::new_chamber_info_packet() {
    return !packets_received.is_empty(CHAMBER_INFO);
}

ClientCommunicator::~ClientCommunicator() {
    this->waiter.join();
    receiver.shutdown();
    sender.shutdown();
}
