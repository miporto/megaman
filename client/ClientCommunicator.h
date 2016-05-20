#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <string>
#include <common/StageInfo.h>

#include "common/Receiver.h"
#include "common/Packet.h"
#include "common/Socket.h"
#include "common/QuitProtected.h"
#include "common/Sender.h"

class ClientReceiver : public Receiver {
    private:
        void receive_packet(const char id);
    public:
        ClientReceiver(Socket& socket,
                       PacketsProtected& packets,
                       QuitProtected& quit);
        ~ClientReceiver();
};

class ClientCommunicator {
    private:
        Socket& socket;
        QuitProtected quit;
        PacketsProtected packets_to_send;
        PacketsProtected packets_received;
        ClientReceiver receiver;

        Packet* pop_from_receiver();
        void push_to_sender(Packet* packet);

    public:
        explicit ClientCommunicator(Socket& socket);
        void send_name(std::string& name);
        void send_stage_pick(char& stage_id);
        StageInfo* receive_stage_info();
        virtual ~ClientCommunicator();
};

#endif //COMMUNICATOR_H
