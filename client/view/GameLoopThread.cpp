#include "client/communication/Client.h"
#include "GameLoopThread.h"
#include "MainWindow.h"
#include "StageSurface.h"

GameLoopThread::GameLoopThread(MainWindow& main_window, Client& client) :
        main_window(main_window), client(client) {}

void GameLoopThread::run() {
    StageSurface stage_surface(client);
    stage_surface.run();
}

void GameLoopThread::join() {
    main_window.resume_stage_pick();
    Thread::join();
}
GameLoopThread::~GameLoopThread() {}
