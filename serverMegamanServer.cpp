#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <stdio.h>

#include "serverMegamanServer.h"
#include "commonAddrInfo.h"
#include "serverAcceptor.h"

void MegamanServer::configure_server_socket() {
	ServerAddrInfo info(port);
	this->server(info());
	this->server.bind_and_listen(info());
}

void MegamanServer::configure_factories() {

}

MegamanServer::MegamanServer(Socket& server, const char* port) :
server(server) {
	configure_server_socket();
	configure_factories();
}

void MegamanServer::operator()() {
	QuitProtected quit;
	Acceptor acceptor(this->server, this->match, quit);
	acceptor.start();
	while(!quit())
		if (getchar() == 'q') quit.switch_to_true();
	this->server.shutdown();
	acceptor.join();
}

MegamanServer::~MegamanServer() {}
