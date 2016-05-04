#include <vector>
#include <string>
#include <sstream>

#include "serverAcceptor.h"
#include "commonThread.h"
#include "commonSocket.h"

QuitProtected::QuitProtected() {
	this->quit = false;
}

void QuitProtected::switch_to_true() {
	Lock l(this->m);
	this->quit = true;
}

bool QuitProtected::operator()() {
	Lock l(this->m);
	return this->quit;
}

QuitProtected::~QuitProtected() {}

Acceptor::Acceptor(Socket& server, QuitProtected& quit) : server(server),
 quit(quit) {}

void Acceptor::run() {
	//int peers_fd;
	while (!this->quit()) {
		try {
			//peers_fd = this->server.accept();
		} catch (const SocketError &e) {
			continue;
		}
		
		//match.add_player(peers_fd)
	}
}

Acceptor::~Acceptor() {}
