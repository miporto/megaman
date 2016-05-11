#include <cstdlib>

#include "common/Socket.h"
#include "Client.h"

#define HOSTNAME_POS 1
#define PORT_POS 2
#define ARGS_LEN 3

int main(int argc, char** argv) {
    if (argc != ARGS_LEN) return EXIT_FAILURE;
	Socket skt;
	Client client(skt, argv[HOSTNAME_POS], argv[PORT_POS]);
	client();
	return EXIT_SUCCESS;
}
