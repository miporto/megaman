#ifndef MEGAMAN_SERVER_H
#define MEGAMAN_SERVER_H

#include <vector>

#include "commonSocket.h"
#include "serverMatch.h"

class MegamanServer {
	private:
		Socket& server;
		//Log log;
		Match match;

		void configure_server_socket(const char* port);
		void configure_factories();

	public:
		MegamanServer(Socket& server, const char* port);
		void operator()();
		~MegamanServer();
};

#endif // MEGAMAN_SERVER_H
