#include "client/communication/Client.h"
#include "GameLoopThread.h"
#include "MainWindow.h"
#include "StageSurface.h"

GameLoopThread::GameLoopThread(MainWindow &main_window, Client &client, char stage_id) :
        main_window(main_window), client(client), stage_id(stage_id) {}

void GameLoopThread::run() {
    StageSurface stage_surface(client);
    stage_surface.run();
    if (stage_surface.game_won()) {
        main_window.set_stage_as_completed(stage_id);
    }
    main_window.resume_stage_pick();
}

GameLoopThread::~GameLoopThread() {}
