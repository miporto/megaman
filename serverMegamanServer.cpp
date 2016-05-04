#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <stdio.h>

#include "serverMegamanServer.h"
#include "commonAddrInfo.h"
#include "serverAcceptor.h"

MegamanServer::MegamanServer(Socket& server, const char* port) :
server(server) {
	ServerAddrInfo info(port);
	this->server(info());
	this->server.bind_and_listen(info());
}

void MegamanServer::operator()() {
	QuitProtected quit;
	Acceptor acceptor(this->server, quit);
	acceptor.start();
	while(!quit())
		if (getchar() == 'q') quit.switch_to_true();
	this->server.shutdown();
	acceptor.join();
}

MegamanServer::~MegamanServer() {}
