#include <stdio.h>

#include "serverMegamanServer.h"
#include "common/commonAddrInfo.h"
#include "serverAcceptor.h"
#include "QuitProtected.h"
#include "serverMatch.h"

void MegamanServer::configure_server_socket(const char* port) {
	ServerAddrInfo info(port);
	this->server(info());
	this->server.bind_and_listen(info());
}

void MegamanServer::configure_factories() {

}

MegamanServer::MegamanServer(Socket& server, const char* port) :
server(server) {
	configure_server_socket(port);
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
