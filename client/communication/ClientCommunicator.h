#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <string>
#include <vector>

#include "common/communication/StageInfo.h"
#include "common/communication/Receiver.h"
#include "common/communication/Packet.h"
#include "common/communication/Socket.h"
#include "common/communication/QuitProtected.h"
#include "common/communication/Sender.h"

class ClientReceiver : public Receiver {
    private:
        void receive_packet(const char id);
    public:
        ClientReceiver(Socket& socket,
                       ReceivedPacketsProtected& packets);
        ~ClientReceiver();
};

class TeamWaiter : public Thread {
    private:
        std::vector<std::string>& teammates;
        ReceivedPacketsProtected& packets_received;
    public:
        TeamWaiter(std::vector<std::string>& teammates,
                   ReceivedPacketsProtected& packets_received);
        void run();
        ~TeamWaiter();
};

class ClientCommunicator {
    private:
        Socket& socket;
        PacketsQueueProtected packets_to_send;
        ReceivedPacketsProtected packets_received;
        ClientReceiver receiver;
        TeamWaiter waiter;

        void push_to_sender(Packet* packet);

    public:
        ClientCommunicator(Socket& socket, std::vector<std::string>& teammates);
        void send_name(std::string& name);
        void send_stage_pick(char& stage_id);
        StageInfo* receive_stage_info();
        virtual ~ClientCommunicator();
};

#endif //COMMUNICATOR_H
