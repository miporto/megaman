#include <queue>
#include <string>

#include "common/Thread.h"
#include "common/Socket.h"
#include "Packet.h"
#include "QuitProtected.h"
#include "Communicator.h"

Receiver::Receiver(SocketProtected& peer,
                   PacketsProtected& packets,
                   QuitProtected& quit)
    : peer(peer), packets(packets), quit(quit) {}

void Receiver::buffer_to_packet() {
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

void Receiver::run() {
    char c;
    while (!this->quit()) {
        try {
            this->peer.receive(&c, sizeof(char));
        }
        catch (const SocketError& e) {
            continue;
        }

        this->buffer << c;
        if (c == '\n')
            buffer_to_packet();
    }
}

Receiver::~Receiver() {}

Sender::Sender(SocketProtected& peer,
               PacketsProtected& packets,
               QuitProtected& quit)
    : peer(peer), packets(packets), quit(quit) {}

void Sender::run() {
    Packet* packet;
    std::string str;
    while (!this->quit()) {
        if (!this->packets.is_empty()) {
            packet = this->packets.pop();
            str = packet->get_str();
            str.push_back('\n');
            try {
                this->peer.send(str.c_str(), sizeof(char) * str.size());
            }
            catch (const SocketError& e) {
                continue;
            }
            delete packet;
        }
    }
}

Sender::~Sender() {}

Communicator::Communicator(int fd)
    : peer(fd),
      sender(peer, packets_to_send, quit),
      receiver(peer, packets_received, quit) {
    this->sender.start();
    this->receiver.start();
}

Packet* Communicator::pop_from_receiver() {
    return this->packets_received.pop();
}

void Communicator::push_to_sender(Packet* packet) {
    this->packets_to_send.push(packet);
}

void Communicator::send_new_player_notification(const std::string& name) {
    this->push_to_sender(new NewPlayer(name));
}

std::string Communicator::receive_name() {
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

void Communicator::shutdown() { this->quit.switch_to_true(); }

Communicator::~Communicator() {
    this->quit.switch_to_true();
    this->peer.shutdown();
    this->sender.join();
    this->receiver.join();
}

HostCommunicator::HostCommunicator(int fd, StageIDProtected& stage_id)
    : Communicator(fd), stage_id(stage_id) {}

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
