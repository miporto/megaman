#ifndef MEGAMAN_CLIENT_H
#define MEGAMAN_CLIENT_H

#include "commonSocket.h"

class MegamanClient {
	private:
		Socket& client;
	
	public:
		MegamanClient(Socket& client, const char* hostname, const char* port);
		void operator()();
		void pick_stage(char stage_id);
		~MegamanClient();
};

#endif // MEGAMAN_CLIENT_H
