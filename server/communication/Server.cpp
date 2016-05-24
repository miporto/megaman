#include "Server.h"
#include "common/AddrInfo.h"
#include "Acceptor.h"

void Server::configure_server_socket(const char* port) {
    ServerAddrInfo info(port);
    this->server(info());
    this->server.bind_and_listen(info());
}

void Server::configure_factories() {
    //TODO
}

Server::Server(Socket& server, const char* port, QuitProtected& quit)
    : quit(quit), server(server), match(communicators) {
    configure_server_socket(port);
    configure_factories();
}

void Server::wait_for_players() {
    QuitProtected quit_acceptor;
    Acceptor acceptor(this->server, this->match, quit_acceptor);
    acceptor.start();
    while (!quit_acceptor() && !this->quit())
        if (this->match.is_full() || this->match.has_started())
            quit_acceptor.switch_to_true();
    acceptor.join();
}

void Server::start_game() { this->match.start_stage(); }

void Server::run() {
    this->wait_for_players();
    if (!this->quit())
        this->start_game();
}

void Server::shutdown() {
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        this->communicators[i]->shutdown();
}

Server::~Server() {
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        delete this->communicators[i];
}
