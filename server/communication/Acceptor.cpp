#include <cstring>
#include <iostream>

#include "Acceptor.h"

Acceptor::Acceptor(Socket& socket, Match* match)
    : quit_acceptor(false), socket(socket), match(match) {
    this->start();
}

void Acceptor::run() {
    Socket* peer;
    while (!this->quit_acceptor) {
        try {
            peer = this->socket.accept();
        }
        catch (const SocketError& e) {
            continue;
        }
        try {
            this->match->add_player(peer);
        }
        catch (const MatchError& e) {
            const char* error_msg = e.what();
            peer->send(error_msg, sizeof(char) * strlen(error_msg));
            peer->shutdown();
            delete peer;
            break;
        }
    }
}

void Acceptor::shutdown() {
    this->quit_acceptor = true;
    this->socket.shutdown();
}

Acceptor::~Acceptor() {
    this->join();
}
