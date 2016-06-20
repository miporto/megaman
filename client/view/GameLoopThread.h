#ifndef MEGAMAN_GAMELOOPTHREAD_H
#define MEGAMAN_GAMELOOPTHREAD_H

#include "common/Thread.h"
#include "client/communication/Client.h"
#include "MainWindow.h"
#include "StageSurface.h"

class MainWindow;

class GameLoopThread : public Thread {
public:
    GameLoopThread(MainWindow &main_window, Client &client, char stage_id);
    void run();
    ~GameLoopThread();
private:
    MainWindow& main_window;
    Client& client;
    char stage_id;
};


#endif //MEGAMAN_GAMELOOPTHREAD_H
