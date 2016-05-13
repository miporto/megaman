#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <sstream>
#include <string>

#include "common/Thread.h"
#include "common/Socket.h"
#include "common/Sender.h"
#include "common/Receiver.h"
#include "common/Packet.h"
#include "common/QuitProtected.h"
#include "Stage.h"

class ServerReceiver : public Receiver {
    public:
        ServerReceiver(SocketProtected& peer,
                     PacketsProtected& packets,
                     QuitProtected& quit);
        void buffer_to_packet();
        ~ServerReceiver();
};

class ServerCommunicator {
    protected:
        SocketProtected peer;
        QuitProtected quit;
        PacketsProtected packets_to_send;
        Sender sender;
        PacketsProtected packets_received;
        ServerReceiver receiver;

        Packet* pop_from_receiver();
        void push_to_sender(Packet* packet);

    public:
        explicit ServerCommunicator(int fd);
        void send_new_player_notification(const std::string& name);
        std::string receive_name();
        void shutdown();
        virtual ~ServerCommunicator();
};

class HostCommunicator : public ServerCommunicator, public Thread {
    private:
        StageIDProtected& stage_id;

    public:
        HostCommunicator(int fd, StageIDProtected& stage_id);
        char check_stage_pick();
        void run();
        ~HostCommunicator();
};

#endif  // COMMUNICATOR_H
