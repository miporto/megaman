#ifndef RECEIVER_H
#define RECEIVER_H

#include <string>

#include "common/Thread.h"
#include "Socket.h"
#include "Packet.h"

class Receiver : public Thread {
    protected:
        Socket* socket;
        ReceivedPacketsProtected& packets;
        bool started, quit;

        virtual void receive_packet(const char id);

    public:
        Receiver(Socket* socket,
                 ReceivedPacketsProtected& packets);
        void start();
        void run();
        void shutdown();
        virtual ~Receiver();
};

class ReceiverError : public SystemError {
public:
    explicit ReceiverError(const std::string error_msg) throw();
};

#endif //RECEIVER_H

