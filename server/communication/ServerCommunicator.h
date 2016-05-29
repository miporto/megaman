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

class NameWaiter : public Thread {
    private:
        Player* player;
        ReceivedPacketsProtected& packets_received;

    public:
        NameWaiter(Player* player, ReceivedPacketsProtected& packets_received);
        void run();
        ~NameWaiter();
};

class ServerCommunicator {
    protected:
        Player* player;
        Socket peer;
        PacketsQueueProtected packets_to_send;
        ReceivedPacketsProtected packets_received;
        Receiver receiver;

    public:
        explicit ServerCommunicator(Player* player, int fd);
        void send_new_player_notification(const std::string& name);
        void send_stage_pick(const char stage_id);
        void receive_name();
        const std::string& name();
        void send_stage_info(const std::string& info);
        virtual void shutdown();
        virtual ~ServerCommunicator();
};

class StageIdWaiter : public Thread {
    private:
        StageIDProtected stage_id;
        ReceivedPacketsProtected& packets_received;

    public:
        explicit StageIdWaiter(ReceivedPacketsProtected& packets_received);
        void run();
        char get_stage_id();
        ~StageIdWaiter();
};

class HostCommunicator : public ServerCommunicator {
    private:
        StageIdWaiter waiter;
    public:
        HostCommunicator(Player* player, int fd);
        char check_stage_id();
        char receive_stage_id();
        ~HostCommunicator();
};

#endif  // COMMUNICATOR_H
