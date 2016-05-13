#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "common/Receiver.h"
#include "common/Packet.h"
#include "common/Socket.h"
#include "common/QuitProtected.h"
#include "common/Sender.h"

class ClientReceiver : public Receiver {
    public:
        ClientReceiver(SocketProtected& socket,
                       PacketsProtected& packets,
                       QuitProtected& quit);
        void buffer_to_packet();
        ~ClientReceiver();
};

class ClientCommunicator {
    private:
        SocketProtected& client;
        QuitProtected quit;
        PacketsProtected packets_to_send;
        Sender sender;
        PacketsProtected packets_received;
        ClientReceiver receiver;

    public:
        explicit ClientCommunicator(SocketProtected& client);
        virtual ~ClientCommunicator();
};

#endif //COMMUNICATOR_H
