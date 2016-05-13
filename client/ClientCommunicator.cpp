#include <string>

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

ClientCommunicator::~ClientCommunicator() {
    this->client.shutdown();
}
