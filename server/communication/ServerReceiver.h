#ifndef SERVERRECEIVER_H
#define SERVERRECEIVER_H

#include "common/communication/Receiver.h"
#include "EventQueue.h"

class ServerReceiver : public Receiver {
    private:
        EventQueue& events;

        void receive_packet(const char id);

    public:
        ServerReceiver(Socket* socket,
                       ReceivedPacketsProtected& packets,
                       EventQueue& events);
        ~ServerReceiver();
};

#endif //SERVERRECEIVER_H
