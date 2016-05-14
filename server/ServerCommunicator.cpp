#include <vector>
#include <string>

#include "ServerCommunicator.h"

ServerReceiver::ServerReceiver(SocketProtected& peer,
                               PacketsProtected& packets,
                               QuitProtected& quit)
        : Receiver(peer, packets, quit) {}

void ServerReceiver::buffer_to_packet() {
    char id;
    this->buffer >> id;

    switch (id) {
        // Solo cases para los paquetes que pueden ser recibidos
        case NEW_PLAYER: {
            std::string name;
            this->buffer >> name;
            this->packets.push(new NewPlayer(name));
            break;
        } case STAGE_PICK: {
            char stage_id;
            this->buffer >> stage_id;
            this->packets.push(new StagePick(stage_id));
            break;
        } default:
            // Si el ID es desconocido, desecha el paquete
            break;
    }

    this->buffer.str("");
}

ServerReceiver::~ServerReceiver() {}

ServerCommunicator::ServerCommunicator(int fd)
    : peer(fd),
      sender(peer, packets_to_send, quit),
      receiver(peer, packets_received, quit) {
    this->sender.start();
    this->receiver.start();
}

Packet* ServerCommunicator::pop_from_receiver() {
    return this->packets_received.pop();
}

void ServerCommunicator::push_to_sender(Packet* packet) {
    this->packets_to_send.push(packet);
}

void ServerCommunicator::send_new_player_notification(const std::string& name) {
    this->push_to_sender(new NewPlayer(name));
}

std::string ServerCommunicator::receive_name() {
    std::string name;
    bool received = false;
    while (!received) {
        if (!this->packets_received.is_empty()) {
            Packet *packet = this->pop_from_receiver();
            if (packet->get_id() == NEW_PLAYER) {
                name = ((NewPlayer*) packet)->get_name();
                received = true;
            }
            delete packet;
        }
    }
    return name;
}

void ServerCommunicator::send_screen_info(ScreenInfo* info) {
    std::vector<char> positions;

    positions = info->get_met_positions();
    for (unsigned int i = 0; i < positions.size(); ++i)
        this->push_to_sender(new StageInfo(MET, positions[i]));
    positions = info->get_bumby_positions();
    for (unsigned int i = 0; i < positions.size(); ++i)
        this->push_to_sender(new StageInfo(BUMBY, positions[i]));
    positions = info->get_sniper_positions();
    for (unsigned int i = 0; i < positions.size(); ++i)
        this->push_to_sender(new StageInfo(SNIPER, positions[i]));
    positions = info->get_jumping_sniper_positions();
    for (unsigned int i = 0; i < positions.size(); ++i)
        this->push_to_sender(new StageInfo(JUMPING_SNIPER, positions[i]));
    positions = info->get_block_positions();
    for (unsigned int i = 0; i < positions.size(); ++i)
        this->push_to_sender(new StageInfo(BLOCK, positions[i]));
    positions = info->get_stairs_positions();
    for (unsigned int i = 0; i < positions.size(); ++i)
        this->push_to_sender(new StageInfo(STAIRS, positions[i]));
    positions = info->get_spike_positions();
    for (unsigned int i = 0; i < positions.size(); ++i)
        this->push_to_sender(new StageInfo(SPIKE, positions[i]));
}

void ServerCommunicator::shutdown() {
    this->quit.switch_to_true();
    this->peer.shutdown();
}

ServerCommunicator::~ServerCommunicator() {
    this->quit.switch_to_true();
    this->peer.shutdown();
    this->sender.join();
    this->receiver.join();
}

HostCommunicator::HostCommunicator(int fd, StageIDProtected& stage_id)
    : ServerCommunicator(fd), stage_id(stage_id) {}

char HostCommunicator::check_stage_pick() {
    char stage_id = 0;
    if (!this->packets_received.is_empty()) {
        Packet* packet = this->pop_from_receiver();
        if (packet->get_id() == STAGE_PICK)
            stage_id = ((StagePick*)packet)->get_stage_id();
        delete packet;
    }
    return stage_id;
}

void HostCommunicator::run() {
    char stage_id;
    do {
        stage_id = this->check_stage_pick();
    } while (!stage_id);
    this->stage_id.set_id(stage_id);
}

HostCommunicator::~HostCommunicator() {}
