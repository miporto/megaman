#include <vector>
#include <queue>

#include "EventQueue.h"

EventQueue::EventQueue(PacketsQueueProtected& received_actions)
        : received_actions(received_actions), quit(false) {
    queue.push(new Action("ROK", 1, true));
}

void EventQueue::run() {
    while (!this->quit) {
        Action *packet;
        if (!this->received_actions.is_empty()) {
            packet = (Action*) this->received_actions.pop();
            Lock l(this->m);
            this->queue.push(packet);
        }
    }
}

bool EventQueue::is_empty() {
    Lock l(this->m);
    return this->queue.size() == 0;
}

Action* EventQueue::pop() {
    Lock l(this->m);
    Action* action = this->queue.front();
    this->queue.pop();
    return action;
}

void EventQueue::shutdown() {
    this->quit = true;
}

EventQueue::~EventQueue() {
    this->shutdown();
    this->join();
}
