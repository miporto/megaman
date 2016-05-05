#include <cstdlib>

#include "common/commonSocket.h"
#include "serverMegamanServer.h"

#define PORT_POS 1

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        return 1;
    }
	Socket skt;
	MegamanServer server(skt, argv[PORT_POS]);
	server();
	return EXIT_SUCCESS;
}
