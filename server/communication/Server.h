#ifndef MEGAMAN_SERVER_H
#define MEGAMAN_SERVER_H

#include <vector>

#include "common/Socket.h"
#include "common/Thread.h"
#include "ServerCommunicator.h"
#include "Match.h"

class Server : public Thread {
   private:
    QuitProtected& quit;
    Socket& server;
    // Log log;
    std::vector<ServerCommunicator*> communicators;
    Match match;

    void configure_server_socket(const char* port);
    void configure_factories();
    void wait_for_players();
    void start_game();

   public:
    Server(Socket& server, const char* port, QuitProtected& quit);
    void run();
    void shutdown();
    ~Server();
};

#endif  // MEGAMAN_SERVER_H
