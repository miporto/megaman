#include <cstring>
#include <iostream>

#include "Acceptor.h"

Acceptor::Acceptor(Socket& server, Match& match, QuitProtected& quit)
    : server(server), match(match), quit(quit) {}

void Acceptor::run() {
    Socket* peer;
    while (!this->quit()) {
        try {
            peer = this->server.accept();
            std::cout << "Accepted"  << std::endl;
        }
        catch (const SocketError& e) {
            continue;
        }
        try {
            this->match.add_player(peer);
        }
        catch (const MatchError& e) {
            const char* error_msg = e.what();
            peer->send(error_msg, sizeof(char) * strlen(error_msg));
            peer->shutdown();
            break;
        }
    }
}

Acceptor::~Acceptor() {}
