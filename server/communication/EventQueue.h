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
        const std::vector<PacketsQueueProtected*> action_queues;
        bool quit;

    public:
        explicit EventQueue
                (const std::vector<PacketsQueueProtected*>& action_queues);
        void run();
        bool is_empty();
        Action* pop();
        void shutdown();
        ~EventQueue();
};

#endif //EVENTQUEUE_H
