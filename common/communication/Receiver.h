#ifndef RECEIVER_H
#define RECEIVER_H

#include <sstream>

#include "common/Thread.h"
#include "Socket.h"
#include "Packet.h"
#include "QuitProtected.h"

class Receiver : public Thread {
    protected:
        Socket& socket;
        ReceivedPacketsProtected& packets;
        bool quit;

        virtual void receive_packet(const char id) = 0;

    public:
        Receiver(Socket& socket,
                 ReceivedPacketsProtected& packets);
        void run();
        void shutdown();
        virtual ~Receiver();
};

#endif //RECEIVER_H

