#include <vector>
#include <string>

#include "ServerCommunicator.h"

ServerReceiver::ServerReceiver(Socket& peer,
                               PacketsProtected& packets,
                               QuitProtected& quit)
        : Receiver(peer, packets, quit) {}

void ServerReceiver::receive_packet(const char id) {
    switch (id) {
        // Solo cases para los paquetes que pueden ser recibidos
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
        } default:
            // Si el ID es desconocido, desecha el paquete
            break;
    }
}

ServerReceiver::~ServerReceiver() {}

ServerCommunicator::ServerCommunicator(int fd)
    : peer(fd),
      receiver(peer, packets_received, quit) {}

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
    this->receiver.run();

    std::string name("");
    if (!this->packets_received.is_empty()) {
        Packet *packet = this->pop_from_receiver();
        if (packet->get_id() == NEW_PLAYER) {
            name = ((NewPlayer*) packet)->get_name();
        }
        delete packet;
    }

    return name;
}

void ServerCommunicator::send_screen_info(StageInfo* info) {
    std::vector<char> positions;

    positions = info->get_met_positions();
    for (unsigned int i = 0; i < positions.size(); ++i)
        this->push_to_sender(new StageElement(MET, positions[i]));
    positions = info->get_bumby_positions();
    for (unsigned int i = 0; i < positions.size(); ++i)
        this->push_to_sender(new StageElement(BUMBY, positions[i]));
    positions = info->get_sniper_positions();
    for (unsigned int i = 0; i < positions.size(); ++i)
        this->push_to_sender(new StageElement(SNIPER, positions[i]));
    positions = info->get_jumping_sniper_positions();
    for (unsigned int i = 0; i < positions.size(); ++i)
        this->push_to_sender(new StageElement(JUMPING_SNIPER, positions[i]));
    positions = info->get_block_positions();
    for (unsigned int i = 0; i < positions.size(); ++i)
        this->push_to_sender(new StageElement(BLOCK, positions[i]));
    positions = info->get_stairs_positions();
    for (unsigned int i = 0; i < positions.size(); ++i)
        this->push_to_sender(new StageElement(STAIRS, positions[i]));
    positions = info->get_spike_positions();
    for (unsigned int i = 0; i < positions.size(); ++i)
        this->push_to_sender(new StageElement(SPIKE, positions[i]));
    positions = info->get_cliff_positions();
    for (unsigned int i = 0; i < positions.size(); ++i)
        this->push_to_sender(new StageElement(CLIFF, positions[i]));

    Sender s(this->peer, this->packets_to_send, this->quit);
}

void ServerCommunicator::shutdown() {
    this->quit.switch_to_true();
    this->peer.shutdown();
}

ServerCommunicator::~ServerCommunicator() {
    this->quit.switch_to_true();
    this->peer.shutdown();
}

HostCommunicator::HostCommunicator(int fd, StageIDProtected& stage_id)
    : ServerCommunicator(fd), stage_id(stage_id) {}

char HostCommunicator::receive_stage_pick() {
    this->receiver.run();

    char stage_id = 0;
    while (!this->packets_received.is_empty()) {
        Packet* packet = this->pop_from_receiver();
        if (packet->get_id() == STAGE_PICK)
            stage_id = ((StagePick *) packet)->get_stage_id();
        delete packet;
    }
    return stage_id;
}

void HostCommunicator::run() {
    char stage_id;
    do {
        stage_id = this->receive_stage_pick();
    } while (!this->quit() && !stage_id);
    this->stage_id.set_id(stage_id);
}

HostCommunicator::~HostCommunicator() {}
