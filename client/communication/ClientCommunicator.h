#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <string>
#include <vector>

#include "common/communication/Receiver.h"
#include "common/communication/Packet.h"
#include "common/communication/Socket.h"
#include "common/communication/QuitProtected.h"
#include "common/communication/Sender.h"

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
        Receiver receiver;
        TeamWaiter waiter;

        void push_to_sender(Packet* packet);

    public:
        ClientCommunicator(Socket& socket, std::vector<std::string>& teammates);
        void send_name(std::string& name);
        void send_stage_pick(char& stage_id);
        const std::string receive_stage_info();
        void send_action(char& action_id, bool pressed);
        virtual ~ClientCommunicator();
};

#endif //COMMUNICATOR_H
