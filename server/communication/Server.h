#ifndef MEGAMAN_SERVER_H
#define MEGAMAN_SERVER_H

#include <vector>

#include "common/communication/Socket.h"
#include "common/Thread.h"
#include "ServerCommunicator.h"
#include "Match.h"
#include "server/Logger.h"

class Acceptor;

class Server : public Thread {
   private:
    bool quit_server;
    Socket socket;
    std::vector<ServerCommunicator*> communicators;
    Match* match;
    Acceptor* acceptor;
    Logger* logger;

    void configure_server_socket(const char* port);
    void wait_for_players();
    void get_rid_of_disconnected_clients();
    void reset_match();

   public:
    explicit Server(const char* port);
    void run();
    void shutdown();
    ~Server();
};

#endif  // MEGAMAN_SERVER_H
