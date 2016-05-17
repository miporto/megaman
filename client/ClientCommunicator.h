#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <string>
#include <common/ScreenInfo.h>

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

        Packet* pop_from_receiver();
        void push_to_sender(Packet* packet);

    public:
        explicit ClientCommunicator(SocketProtected& client);
        void start_communication();
        void send_name(std::string& name);
        void send_stage_pick(char& stage_id);
        ScreenInfo* receive_stage_info();
        virtual ~ClientCommunicator();
};

#endif //COMMUNICATOR_H
