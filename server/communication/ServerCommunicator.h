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
                       ReceivedPacketsProtected& packets);
        ~ServerReceiver();
};

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
        ServerReceiver receiver;

    public:
        explicit ServerCommunicator(Player* player, int fd);
        void send_new_player_notification(const std::string& name);
        void send_stage_pick(const char stage_id);
        void receive_name();
        const std::string& name();
        void send_stage_info(StageInfo* info);
        virtual void shutdown();
        virtual ~ServerCommunicator();
};

class StageIdWaiter : public Thread {
    private:
        StageIDProtected& stage_id;
        ReceivedPacketsProtected& packets_received;

    public:
        StageIdWaiter(StageIDProtected& stage_id,
                      ReceivedPacketsProtected& packets_received);
        void run();
        ~StageIdWaiter();
};

class HostCommunicator : public ServerCommunicator {
    private:
        StageIdWaiter waiter;
    public:
        HostCommunicator(Player* player, int fd, StageIDProtected& stage_id);
        void receive_stage_id();
        ~HostCommunicator();
};

#endif  // COMMUNICATOR_H
