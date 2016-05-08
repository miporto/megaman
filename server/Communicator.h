#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <sstream>

#include "common/Thread.h"
#include "common/Socket.h"
#include "Packet.h"
#include "QuitProtected.h"

class Receiver: public Thread {
    private:
        SocketProtected& peer;
        std::stringstream buffer;
        PacketsProtected& packets;
        QuitProtected& quit;

    public:
        Receiver(SocketProtected& peer, PacketsProtected& packets, QuitProtected& quit);
        void buffer_to_packet();
        void run();
        ~Receiver();
};

class Sender : public Thread {
    private:
        SocketProtected& peer;
        PacketsProtected& packets;
        QuitProtected& quit;

    public:
        Sender(SocketProtected& peer, PacketsProtected& packets, QuitProtected& quit);
        void run();
        ~Sender();
};

class Communicator {
    private:
        SocketProtected peer;
        QuitProtected quit;
        PacketsProtected packets_to_send;
        Sender sender;
        PacketsProtected packets_received;
        Receiver receiver;

        Packet* pop_from_receiver();
        void push_to_sender(Packet* packet);

    public:
        Communicator(int fd);
        void send_new_player_notification();
        int check_stage_pick();
        ~Communicator();
};

#endif //COMMUNICATOR_H