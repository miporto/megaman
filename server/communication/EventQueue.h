#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <vector>
#include <queue>

#include "common/Thread.h"
#include "common/communication/Packet.h"

class EventQueue : public Thread {
    private:
        Mutex m;
        std::queue<Action*> queue;
        PacketsQueueProtected& received_actions;
        bool quit;

    public:
        explicit EventQueue(PacketsQueueProtected& received_actions);
        void run();
        bool is_empty();
        Action* pop();
        void shutdown();
        ~EventQueue();
};

#endif //EVENTQUEUE_H
