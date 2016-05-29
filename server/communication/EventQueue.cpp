#include <vector>
#include <queue>

#include "EventQueue.h"

EventQueue::EventQueue(PacketsQueueProtected& received_actions)
        : received_actions(received_actions), quit(false) {}

void EventQueue::run() {
    while (!this->quit) {
        Action *packet;
        if (!this->received_actions.is_empty()) {
            packet = (Action*) this->received_actions.pop();
            this->queue.push(packet);
        }
    }
}

void EventQueue::shutdown() {
    this->quit = true;
}

EventQueue::~EventQueue() {
    this->shutdown();
    this->join();
}
