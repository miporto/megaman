#ifndef MEGAMAN_WAITINGROOMTHREAD_H
#define MEGAMAN_WAITINGROOMTHREAD_H

#include <string>
#include <vector>

#include "common/Thread.h"
#include "client/communication/Client.h"
#include "MainWindow.h"

class WaitingRoomThread : public Thread {
public:
    WaitingRoomThread(MainWindow &window, Client &client);
    void run();
    ~WaitingRoomThread();
private:
    void send_teammates();
    MainWindow &window;
    Client &client;
    std::vector<std::string> teammates;
};

#endif //MEGAMAN_WAITINGROOMTHREAD_H
