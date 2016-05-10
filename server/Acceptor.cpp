#include <cstring>

#include "Acceptor.h"

Acceptor::Acceptor(Socket& server, Match& match, QuitProtected& quit) :
	server(server), match(match), quit(quit) {}

void Acceptor::run() {
	int peers_fd;
	while (!this->quit()) {
		try {
			peers_fd = this->server.accept();
		} catch (const SocketError &e) {
			break;
		}
		try {
			this->match.add_player(peers_fd);
		} catch (const MatchError &e) {
			Socket skt(peers_fd);
			const char* error_msg = e.what();
			skt.send(error_msg, sizeof(char) * strlen(error_msg));
			skt.shutdown();
			break;
		}
	}
}

Acceptor::~Acceptor() {}
