#ifndef SENDER_H
#define SENDER_H

#include "Socket.h"
#include "Packet.h"
#include "QuitProtected.h"

class Sender : public Thread {
    private:
        SocketProtected& socket;
        PacketsProtected& packets;
        QuitProtected& quit;

    public:
        Sender(SocketProtected& socket,
               PacketsProtected& packets,
               QuitProtected& quit);
        void run();
        ~Sender();
};

#endif //SENDER_H
