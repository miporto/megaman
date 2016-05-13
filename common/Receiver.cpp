#include "Receiver.h"

Receiver::Receiver(SocketProtected& socket,
                   PacketsProtected& packets,
                   QuitProtected& quit)
        : socket(socket), packets(packets), quit(quit) {}

void Receiver::run() {
    char c;
    while (!this->quit()) {
        try {
            this->socket.receive(&c, sizeof(char));
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
