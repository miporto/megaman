#include <unistd.h>

#include "Server.h"
#include "common/communication/AddrInfo.h"
#include "Acceptor.h"

#define SLEEP_TIME_MICROSECONDS 1000000

void Server::configure_server_socket(const char* port) {
    ServerAddrInfo info(port);
    this->socket(info());
    this->socket.bind_and_listen(info());
}

Server::Server(const char* port)
    : quit_server(false), match(NULL),
      acceptor(NULL), logger(Logger::instance()) {
    this->match = new Match(communicators);
    this->acceptor = new Acceptor(this->socket, this->match);
    this->configure_server_socket(port);
    this->start();
}

void Server::wait_for_players() {
    //Acceptor acceptor(this->socket, this->match);

    while (!this->quit_server &&
           !this->match->is_full() && !this->match->has_started())
        usleep(SLEEP_TIME_MICROSECONDS);

    //acceptor.shutdown();
}

void Server::run() {
    while (!this->quit_server && !this->match->ended()) {
        this->wait_for_players();
        if (!this->quit_server) this->match->play_stage(&this->quit_server);
        this->get_rid_of_disconnected_clients();
    }
}

void Server::get_rid_of_disconnected_clients() {
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        if (this->communicators[i]->disconnected()) {
            this->communicators.erase(this->communicators.begin() + i);
            delete this->communicators[i];

            if (i == 0) this->reset_match();
        }
}

void Server::reset_match() {
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        this->communicators[i]->shutdown();
    for (unsigned int i = 0; i < this->communicators.size(); ++i) {
        this->communicators.erase(this->communicators.begin() + i);
        delete this->communicators[i];
    }
    delete this->match;
    this->match = new Match(this->communicators);
}

void Server::shutdown() {
    this->quit_server = true;
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        this->communicators[i]->shutdown();
    this->acceptor->shutdown();
}

Server::~Server() {
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        delete this->communicators[i];
    delete logger;
    delete match;
    delete acceptor;
}
