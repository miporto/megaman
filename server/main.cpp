#include <cstdlib>
#include <cstdio>

#include "common/communication/Socket.h"
#include "server/communication/Server.h"

#define PORT_POS 1
#define ARGS_LEN 2

int main(int argc, const char* argv[]) {
//    if (argc != ARGS_LEN)
//        return EXIT_FAILURE;

    bool quit_main = false;

    Server server(argv[PORT_POS]);

    while (!quit_main)
        if (getchar() == 'q') {
            quit_main = true;
            server.shutdown();
            server.join();
        }

    return EXIT_SUCCESS;
}
