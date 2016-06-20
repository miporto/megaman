#include <unistd.h>
#include <vector>

#include "server/model/Factory.h"
#include "Server.h"
#include "common/communication/AddrInfo.h"
#include "Acceptor.h"

#define SLEEP_TIME_MICROSECONDS 1000000

void Server::configure_server_socket(const char* port) {
    if (!port) port = ConnectionConfiguration::port().c_str();
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
    while (!this->quit_server &&
           !this->match->is_full() && !this->match->has_started())
        usleep(SLEEP_TIME_MICROSECONDS);
}

void Server::run() {
    while (!this->quit_server) {
        this->wait_for_players();
        if (!this->quit_server) this->match->play_stage(&this->quit_server);
        if (!this->quit_server) this->get_rid_of_disconnected_clients();
        if (this->match->ended()) this->reset_match();
    }
}

void Server::get_rid_of_disconnected_clients() {
    for (std::vector<ServerCommunicator*>::iterator it = this->communicators.begin();
         it != this->communicators.end();) {
        if ((*it)->disconnected()) {
            // Si el Host esta desconectado, el Match se reinicia
            if (it == this->communicators.begin()) {
                this->reset_match();
                break;
            }
            delete (*it);
            it = this->communicators.erase(it);
        } else {
            ++it;
        }
    }
}

void Server::reset_match() {
    // Clients shutdown & close
    for (unsigned int i = 0; i < this->communicators.size(); ++i) {
        if (!this->communicators[i]->disconnected())
            this->communicators[i]->shutdown();
        delete this->communicators[i];
    }

    this->communicators.clear();
    delete this->match;
    this->match = new Match(this->communicators);
    this->acceptor->set_match(this->match);
}

void Server::shutdown() {
    Logger::instance()->out << INFO << "Server shutdown";
    this->quit_server = true;
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        if (!this->communicators[i]->disconnected())
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
