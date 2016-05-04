#include <vector>
#include <string>
#include <sstream>

#include "serverAcceptor.h"
#include "commonThread.h"
#include "commonSocket.h"

#define PLAYERS_MAX 4

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
	for (unsigned int i = 0; !this->quit() && i < PLAYERS_MAX; ++i) {
		/* Agregar condicion de corte de host iniciando la partida
		 * antes de que se unan 4 jugadores
		 */
		try {
			//peers_fd = this->server.accept();
		} catch (const SocketError &e) {
			continue;
		}
		
		//match.add_player(peers_fd)
	}
}

Acceptor::~Acceptor() {}
