#include <queue>

#include "common/Thread.h"
#include "common/Socket.h"
#include "QuitProtected.h"
#include "Communicator.h"

char BufferProtected::pop_char() {
    Lock l(this->m);
    char c = this->queue.front();
    this->queue.pop();
    return c;
}
void BufferProtected::push_char(char c) {
    Lock l(this->m);
    this->queue.push(c);
}

bool BufferProtected::is_empty() {
    return this->queue.size() == 0;
}

BufferProtected::~BufferProtected() {}

Receiver::Receiver(SocketProtected& peer, BufferProtected& buffer, QuitProtected& quit) :
    peer(peer), buffer(buffer), quit(quit) {}

void Receiver::run() {
    char c;
    while (!this->quit()) {
        try {
            this->peer.receive(&c, sizeof(char));
        } catch (const SocketError &e) {
            continue;
        }
        this->buffer.push_char(c);
    }
}

Receiver::~Receiver() {}

Sender::Sender(SocketProtected& peer, BufferProtected& buffer, QuitProtected& quit) :
    peer(peer), buffer(buffer), quit(quit) {}

void Sender::run() {
    char c;
    while (!this->quit()) {
        if (!this->buffer.is_empty()) {
            c = this->buffer.pop_char();
            try {
                this->peer.send(&c, sizeof(char));
            } catch (const SocketError &e) {
                continue;
            }
        }
    }
}

Sender::~Sender() {}

Communicator::Communicator(int fd) : peer(fd),
    sender(peer, sender_buffer, quit), receiver(peer, receiver_buffer, quit) {
    this->sender.start();
    this->receiver.start();
}

char Communicator::pop_from_receiver() {
    return this->receiver_buffer.pop_char();
}

void Communicator::push_to_sender(char c) {
    this->sender_buffer.push_char(c);
}

void Communicator::stop() {
    this->quit.switch_to_true();
    this->peer.shutdown();
}

Communicator::~Communicator() {
    this->sender.join();
    this->receiver.join();
}
