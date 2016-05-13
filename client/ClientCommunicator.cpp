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
            //TODO
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

ClientCommunicator::~ClientCommunicator() {}
