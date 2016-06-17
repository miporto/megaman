#ifndef MEGAMAN_WAITINGROOMTHREAD_H
#define MEGAMAN_WAITINGROOMTHREAD_H

#include <string>
#include <vector>

#include "common/Thread.h"
#include "client/communication/Client.h"
#include "MainWindow.h"

class MainWindow;
class WaitingRoomThread : public Thread {
public:
    WaitingRoomThread(MainWindow &window, Client &client);
    void run();
    void end_waiting();
    ~WaitingRoomThread();
private:
    void send_new_teammates(std::vector<std::string> &new_teammates);
    MainWindow &window;
    Client &client;
    std::vector<std::string> teammates;
    bool end = false;
};

#endif //MEGAMAN_WAITINGROOMTHREAD_H
