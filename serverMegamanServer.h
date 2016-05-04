#ifndef MEGAMAN_SERVER_H
#define MEGAMAN_SERVER_H

#include <vector>

#include "commonSocket.h"

class MegamanServer {
	private:
		Socket& server;

	public:
		MegamanServer(Socket& server, const char* port);
		void operator()();
		~MegamanServer();
};

#endif // MEGAMAN_SERVER_H
