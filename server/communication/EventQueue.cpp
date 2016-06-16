#include <vector>
#include <queue>

#include "EventQueue.h"

void EventQueue::flush_previous_actions() {
    while (!this->queue.empty()) {
        delete this->queue.front();
        this->queue.pop();
    }
}

void EventQueue::push(Action* action) {
    Lock l(this->m);
    this->queue.push(action);
}

bool EventQueue::is_empty() {
    Lock l(this->m);
    return this->queue.empty();
}

Action* EventQueue::pop() {
    Lock l(this->m);
    Action* action = this->queue.front();
    this->queue.pop();
    return action;
}

EventQueue::~EventQueue() {
    while (!this->queue.empty()) {
        delete this->queue.front();
        this->queue.pop();
    }
}
