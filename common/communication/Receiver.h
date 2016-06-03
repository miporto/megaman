#ifndef RECEIVER_H
#define RECEIVER_H

#include <sstream>

#include "common/Thread.h"
#include "Socket.h"
#include "Packet.h"
#include "QuitProtected.h"

class Receiver : public Thread {
    protected:
        Socket* socket;
        ReceivedPacketsProtected& packets;
        bool started, quit;

        void receive_packet(const char id);

    public:
        Receiver(Socket* socket,
                 ReceivedPacketsProtected& packets);
        void start();
        void run();
        void shutdown();
        ~Receiver();
};

#endif //RECEIVER_H

