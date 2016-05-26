#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <sstream>
#include <string>

#include "common/Thread.h"
#include "common/communication/Socket.h"
#include "common/communication/Sender.h"
#include "common/communication/Receiver.h"
#include "common/communication/Packet.h"
#include "common/communication/QuitProtected.h"
#include "Stage.h"

class ServerReceiver : public Receiver {
    private:
        void receive_packet(const char id);
    public:
        ServerReceiver(Socket& peer,
                     PacketsProtected& packets,
                     QuitProtected& quit);
        ~ServerReceiver();
};

class ServerCommunicator {
    protected:
        Socket peer;
        QuitProtected quit;
        PacketsProtected packets_to_send;
        PacketsProtected packets_received;
        ServerReceiver receiver;

        Packet* pop_from_receiver();
        void push_to_sender(Packet* packet);

    public:
        explicit ServerCommunicator(int fd);
        void send_new_player_notification(const std::string& name);
        std::string receive_name();
        void send_stage_info(StageInfo* info);
        void shutdown();
        virtual ~ServerCommunicator();
};

class HostCommunicator : public ServerCommunicator, public Thread {
    private:
        StageIDProtected& stage_id;
        char receive_stage_pick();

    public:
        HostCommunicator(int fd, StageIDProtected& stage_id);
        void run();
        ~HostCommunicator();
};

#endif  // COMMUNICATOR_H
