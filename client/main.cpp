#include <cstdlib>

#include "common/Socket.h"
#include "Client.h"

#define HOSTNAME_POS 1
#define PORT_POS 2

int main(int argc, char** argv) {
    if (argc != 3) return 1;
	Socket skt;
	MegamanClient client(skt, argv[HOSTNAME_POS], argv[PORT_POS]);
	client();
	return EXIT_SUCCESS;
}
