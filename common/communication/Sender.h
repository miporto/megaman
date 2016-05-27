#ifndef SENDER_H
#define SENDER_H

#include "Socket.h"
#include "Packet.h"
#include "QuitProtected.h"

class Sender : public Thread {
    private:
        Socket& socket;
        PacketsQueueProtected& packets;

    public:
        Sender(Socket& socket,
               PacketsQueueProtected& packets);
        void run();
        ~Sender();
};

#endif //SENDER_H
