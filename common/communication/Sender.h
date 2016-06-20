#ifndef SENDER_H
#define SENDER_H

#include "Socket.h"
#include "Packet.h"
#include "QuitProtected.h"

class Sender : public Thread {
    private:
        Socket* socket;
        PacketsQueueProtected& packets;
        bool started, quit;

    public:
        Sender(Socket* socket,
               PacketsQueueProtected& packets);
        void start();
        void run();
        void shutdown();
        ~Sender();
};

#endif //SENDER_H
