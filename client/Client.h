#ifndef MEGAMAN_CLIENT_H
#define MEGAMAN_CLIENT_H

#include "common/Socket.h"

class Client {
	private:
		Socket& client;
	
	public:
		Client(Socket& client, const char* hostname, const char* port);
		void operator()();
		void pick_stage(char stage_id);
		~Client();
};

#endif // MEGAMAN_CLIENT_H
