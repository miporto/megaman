#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <vector>
#include <queue>

#include "common/Thread.h"
#include "common/communication/Packet.h"

class EventQueue : public Thread {
    private:
        std::queue<Action*> queue;
        PacketsQueueProtected& received_actions;
        bool quit;

    public:
        explicit EventQueue(PacketsQueueProtected& received_actions);
        void run();
        void shutdown();
        ~EventQueue();
};

#endif //EVENTQUEUE_H
