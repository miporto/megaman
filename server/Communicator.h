#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <sstream>

#include "common/Thread.h"
#include "common/Socket.h"
#include "Packet.h"
#include "QuitProtected.h"
#include "Stage.h"

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
    protected: //TODO: Pablo me va a fajar
        SocketProtected peer;
        QuitProtected quit;
        PacketsProtected packets_to_send;
        Sender sender;
        PacketsProtected packets_received;
        Receiver receiver;

        Packet* pop_from_receiver();
        void push_to_sender(Packet* packet);

    public:
        explicit Communicator(int fd);
        void send_new_player_notification();
        void shutdown();
        virtual ~Communicator();
};

class HostCommunicator : public Communicator, public Thread {
    private:
        StageIDProtected& stage_id;

    public:
        explicit HostCommunicator(int fd, StageIDProtected& stage_id);
        char check_stage_pick();
        void run();
        ~HostCommunicator();
};

#endif //COMMUNICATOR_H