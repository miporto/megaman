#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <string>
#include <vector>
#include <utility>


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

typedef std::pair<std::string, std::string> UpdatePacket;
class ClientCommunicator {
    private:
        Socket& socket;
        PacketsQueueProtected packets_to_send;
        Sender sender;
        ReceivedPacketsProtected packets_received;
        Receiver receiver;
        TeamWaiter waiter;

    public:
        ClientCommunicator(Socket& socket, std::vector<std::string>& teammates);
        void send_name(std::string& name);
        void send_stage_pick(char& stage_id);
        const std::string receive_stage_info();
        UpdatePacket receive_update();
        int receive_deceased();
        void send_action(const std::string& name, const char& action_id,
                         const bool& pressed);
        bool new_update_packets();
        bool new_deceased();
        virtual ~ClientCommunicator();
};

#endif //COMMUNICATOR_H
