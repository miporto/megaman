#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "common/Socket.h"
#include "Server.h"

#define PORT_POS 1
#define ARGS_LEN 2

int main(int argc, const char* argv[]) {
    if (ARGS_LEN != 2) return EXIT_FAILURE;
	QuitProtected quit;

	Socket skt;
	Server server(skt, argv[PORT_POS], quit);
	server.start();

	while (!quit())
		if (getchar() == 'q')
		    quit.switch_to_true();

	skt.shutdown();
	server.shutdown();
	server.join();

	return EXIT_SUCCESS;
}

