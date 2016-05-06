#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <queue>

#include "common/Thread.h"
#include "common/Socket.h"
#include "QuitProtected.h"

class BufferProtected {
private:
    Mutex m;
    std::queue<char> queue;

public:
    char pop_char();
    void push_char(char c);
    bool is_empty();
    ~BufferProtected();
};

class Receiver: public Thread {
    private:
        SocketProtected& peer;
        BufferProtected& buffer;
        QuitProtected& quit;

    public:
        Receiver(SocketProtected& peer, BufferProtected& buffer, QuitProtected& quit);
        void run();
        ~Receiver();
};

class Sender : public Thread {
    private:
        SocketProtected& peer;
        BufferProtected& buffer;
        QuitProtected& quit;

    public:
        Sender(SocketProtected& peer, BufferProtected& buffer, QuitProtected& quit);
        void run();
        ~Sender();
};

class Communicator {
    private:
        SocketProtected peer;
        QuitProtected quit;
        BufferProtected sender_buffer;
        Sender sender;
        BufferProtected receiver_buffer;
        Receiver receiver;

    public:
        Communicator(int fd);
        char pop_from_receiver();
        void push_to_sender(char c);
        void stop();
        ~Communicator();
};

#endif //COMMUNICATOR_H
