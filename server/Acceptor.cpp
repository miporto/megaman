#include "Acceptor.h"
#include "common/Thread.h"
#include "common/Socket.h"
#include "QuitProtected.h"
#include "Match.h"

Acceptor::Acceptor(Socket& server, Match& match, QuitProtected& quit) :
	server(server), match(match), quit(quit) {}

void Acceptor::run() {
	int peers_fd;
	//Cambio el for (i < PLAYERS_MAX) por while, las demas condiciones las chequea el propio Match
	while (!this->quit()) {
		try {
			peers_fd = this->server.accept();
			this->match.add_player(peers_fd);
		} catch (const SocketError &e) {
			continue;
		} catch (const MatchError &e) {
			break;
		}
	}
	this->quit.switch_to_true();
}

Acceptor::~Acceptor() {}
