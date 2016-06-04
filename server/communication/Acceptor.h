#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "common/communication/Socket.h"
#include "common/Thread.h"
#include "common/communication/QuitProtected.h"
#include "Match.h"

class Acceptor : public Thread {
    private:
        bool quit_acceptor;
        Socket& socket;
        Match& match;

   public:
        Acceptor(Socket& socket, Match& match);
        void run();
        void shutdown();
        ~Acceptor();
};

#endif  // ACCEPTOR_H
