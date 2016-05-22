#include <string>
#include <vector>

#include "client/ClientCommunicator.h"

ClientReceiver::ClientReceiver(Socket& socket,
                               PacketsProtected& packets,
                               QuitProtected& quit)
        : Receiver(socket, packets, quit) {}

void ClientReceiver::receive_packet(const char id) {
    switch (id) {
        // Solo cases para los paquetes que pueden ser recibidos
        case STAGE_ELEMENT: {
            char type;
            int x, y;
            this->socket.receive(&type, sizeof(char));
            this->socket.receive((char*)&x, sizeof(int));
            this->socket.receive((char*)&y, sizeof(int));
            this->packets.push(new StageElement(type, new Position(x, y)));
            break;
        } default:
            // Si el ID es desconocido, desecha el paquete
            break;
    }
}

ClientReceiver::~ClientReceiver() {}

ClientCommunicator::ClientCommunicator(Socket& socket)
        : socket(socket),
          receiver(socket, this->packets_received, this->quit) {}

Packet* ClientCommunicator::pop_from_receiver() {
    return this->packets_received.pop();
}

void ClientCommunicator::push_to_sender(Packet* packet) {
    this->packets_to_send.push(packet);
    Sender s(this->socket, this->packets_to_send, this->quit);
}

void ClientCommunicator::send_name(std::string& name) {
    this->push_to_sender(new NewPlayer(name));
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

    this->receiver.run();

    while (!this->packets_received.is_empty()) {
        Packet* packet = this->pop_from_receiver();

        if (packet->get_id() == STAGE_ELEMENT) {
            StageElement* stage_element = (StageElement*) packet;
            switch (stage_element->get_type()) {
                case MET:
                    met_positions.push_back
                            (stage_element->get_position());
                    break;
                case BUMBY:
                    bumby_positions.push_back
                            (stage_element->get_position());
                    break;
                case SNIPER:
                    sniper_positions.push_back
                            (stage_element->get_position());
                    break;
                case JUMPING_SNIPER:
                    jumping_sniper_positions.push_back
                            (stage_element->get_position());
                    break;
                case BLOCK:
                    block_positions.push_back
                            (stage_element->get_position());
                    break;
                case STAIRS:
                    stairs_positions.push_back
                            (stage_element->get_position());
                    break;
                case SPIKE:
                    spike_positions.push_back
                            (stage_element->get_position());
                    break;
                case CLIFF:
                    cliff_positions.push_back
                            (stage_element->get_position());
                    break;
                default:
                    break;
            }
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

ClientCommunicator::~ClientCommunicator() {}
