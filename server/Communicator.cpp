#include <queue>

#include "common/commonThread.h"
#include "common/commonSocket.h"
#include "QuitProtected.h"
#include "Communicator.h"

char BufferProtected::get_char() {
    Lock l(this->m);
    char c = this->queue.front();
    this->queue.pop();
    return c;
}
void BufferProtected::append_char(char c) {
    Lock l(this->m);
    this->queue.push(c);
}

BufferProtected::~BufferProtected() {}

Receiver::Receiver(Socket& peer, BufferProtected& buffer, QuitProtected& quit) :
    peer(peer), buffer(buffer), quit(quit) {}

void Receiver::run() {
    char c;
    while (!this->quit()) {
        try {
            this->peer.receive(&c, sizeof(char));
        } catch (const SocketError &e) {
            continue;
        }
        this->buffer.append_char(c);
    }
}

Receiver::~Receiver() {}

Sender::Sender(Socket& peer, BufferProtected& buffer, QuitProtected& quit) :
    peer(peer), buffer(buffer), quit(quit) {}

void Sender::run() {
    char c;
    while (!this->quit()) {
        c = this->buffer.get_char(); //si es vacio q hacemo, guarda con hacer un isEmpty por la race cond
        try {
            this->peer.send(&c, sizeof(char));
        } catch (const SocketError &e) {
            continue;
        }
    }
}

Sender::~Sender() {}

Communicator::Communicator(int fd) : peer(fd),
    sender(peer, sender_buffer, quit), receiver(peer, receiver_buffer, quit) {
    this->sender.start();
    this->receiver.start();
}

void Communicator::stop() {
    this->quit.switch_to_true();
    this->peer.shutdown();
}

Communicator::~Communicator() {
    this->sender.join();
    this->receiver.join();
}