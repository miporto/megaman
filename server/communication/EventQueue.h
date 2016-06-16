#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <queue>

#include "common/Thread.h"
#include "common/communication/Packet.h"

class EventQueue {
    private:
        Mutex m;
        std::queue<Action*> queue;

    public:
        void push(Action* action);
        bool is_empty();
        Action* pop();
        void flush_previous_actions();
        ~EventQueue();
};

#endif //EVENTQUEUE_H
