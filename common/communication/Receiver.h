#ifndef RECEIVER_H
#define RECEIVER_H

#include <sstream>

#include "common/Thread.h"
#include "Socket.h"
#include "Packet.h"
#include "QuitProtected.h"

class Receiver {
    protected:
        Socket& socket;
        PacketsProtected& packets;
        QuitProtected& quit;

        virtual void receive_packet(const char id) = 0;

    public:
        Receiver(Socket& socket,
                 PacketsProtected& packets,
                 QuitProtected& quit);

        void run();
        virtual ~Receiver();
};

#endif //RECEIVER_H

