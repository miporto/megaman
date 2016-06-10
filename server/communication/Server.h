#ifndef MEGAMAN_SERVER_H
#define MEGAMAN_SERVER_H

#include <vector>

#include "common/communication/Socket.h"
#include "common/Thread.h"
#include "ServerCommunicator.h"
#include "Match.h"
#include "server/Logger.h"

class Server : public Thread {
   private:
    bool quit_server;
    Socket socket;
    std::vector<ServerCommunicator*> communicators;
    Match match;
    Logger* logger;

    void configure_server_socket(const char* port);
    void wait_for_players();

   public:
    explicit Server(const char* port);
    void run();
    void shutdown();
    ~Server();
};

#endif  // MEGAMAN_SERVER_H
