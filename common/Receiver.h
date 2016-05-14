#ifndef RECEIVER_H
#define RECEIVER_H

#include <sstream>

#include "Thread.h"
#include "Socket.h"
#include "Packet.h"
#include "QuitProtected.h"

class Receiver : public Thread {
    protected:
        SocketProtected& socket;
        std::stringstream buffer;
        PacketsProtected& packets;
        QuitProtected& quit;

    public:
        Receiver(SocketProtected& socket,
                 PacketsProtected& packets,
                 QuitProtected& quit);
        virtual void buffer_to_packet() = 0;
        void run();
        virtual ~Receiver();
};

#endif //RECEIVER_H

