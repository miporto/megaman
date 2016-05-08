#ifndef MEGAMAN_SERVER_H
#define MEGAMAN_SERVER_H

#include <vector>

#include "common/Socket.h"
#include "Match.h"
#include "Communicator.h"

class Server {
	private:
		Socket& server;
		//Log log;
		std::vector<Communicator*> communicators;
		Match match;

		void configure_server_socket(const char* port);
		void configure_factories();

	public:
		Server(Socket& server, const char* port);
		void operator()();
		~Server();
};

#endif // MEGAMAN_SERVER_H
