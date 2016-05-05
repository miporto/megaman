#include <cstdlib>

#include "common/commonSocket.h"
#include "serverMegamanServer.h"

#define PORT_POS 1

int main(int argc, const char* argv[]) {
	Socket skt;
	MegamanServer server(skt, argv[PORT_POS]);
	server();
	return EXIT_SUCCESS;
}
