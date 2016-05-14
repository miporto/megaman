#include <string>
#include <vector>

#include "client/ClientCommunicator.h"

ClientReceiver::ClientReceiver(SocketProtected& socket,
                               PacketsProtected& packets,
                               QuitProtected& quit)
        : Receiver(socket, packets, quit) {}

void ClientReceiver::buffer_to_packet() {
    char id;
    this->buffer >> id;

    switch (id) {
        // Solo cases para los paquetes que pueden ser recibidos
        case STAGE_INFO: {
            char type, position;
            this->buffer >> type;
            this->buffer >> position;
            this->packets.push(new StageInfo(type, position));
            break;
        } default:
            // Si el ID es desconocido, desecha el paquete
            break;
    }

    this->buffer.str("");
}

ClientReceiver::~ClientReceiver() {}

ClientCommunicator::ClientCommunicator(SocketProtected& client)
        : client(this->client),
          sender(this->client, this->packets_to_send, this->quit),
          receiver(this->client, this->packets_received, this->quit) {
    this->sender.start();
    this->receiver.start();
}

Packet* ClientCommunicator::pop_from_receiver() {
    return this->packets_received.pop();
}

void ClientCommunicator::push_to_sender(Packet* packet) {
    this->packets_to_send.push(packet);
}

void ClientCommunicator::send_name(std::string& name) {
    this->push_to_sender(new NewPlayer(name));
}

void ClientCommunicator::send_stage_pick(char& stage_id) {
    this->push_to_sender(new StagePick(stage_id));
}

ScreenInfo* ClientCommunicator::receive_stage_info() {
    std::vector<char> met_positions;
    std::vector<char> bumby_positions;
    std::vector<char> sniper_positions;
    std::vector<char> jumping_sniper_positions;
    std::vector<char> block_positions;
    std::vector<char> stairs_positions;
    std::vector<char> spike_positions;

    while (!this->packets_received.is_empty()) {
        Packet* packet = this->pop_from_receiver();

        if (packet->get_id() == STAGE_INFO) {
            StageInfo* stage_info = (StageInfo*) packet;
            switch (stage_info->get_type()) {
                case MET:
                    met_positions.push_back
                            (stage_info->get_position());
                    break;
                case BUMBY:
                    bumby_positions.push_back
                            (stage_info->get_position());
                    break;
                case SNIPER:
                    sniper_positions.push_back
                            (stage_info->get_position());
                    break;
                case JUMPING_SNIPER:
                    jumping_sniper_positions.push_back
                            (stage_info->get_position());
                    break;
                case BLOCK:
                    block_positions.push_back
                            (stage_info->get_position());
                    break;
                case STAIRS:
                    stairs_positions.push_back
                            (stage_info->get_position());
                    break;
                case SPIKE:
                    spike_positions.push_back
                            (stage_info->get_position());
                    break;
                default:
                    break;
            }
        }
        delete packet;
    }

    return new ScreenInfo(met_positions,
                          bumby_positions,
                          sniper_positions,
                          jumping_sniper_positions,
                          block_positions,
                          stairs_positions,
                          spike_positions);
}

ClientCommunicator::~ClientCommunicator() {
    this->client.shutdown();
}
