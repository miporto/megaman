#include <string>
#include <vector>

#include "common/Thread.h"
#include "client/communication/Client.h"
#include "MainWindow.h"
#include "WaitingRoomThread.h"

WaitingRoomThread::WaitingRoomThread(MainWindow &window, Client &client) :
        window(window), client(client){
    teammates = client.get_teammates();
}

void WaitingRoomThread::run() {
    while (!client.new_stage_pick()) {
        std::vector<std::string> new_teammates = client.get_teammates();
        send_new_teammates(new_teammates);
        teammates = new_teammates;
        usleep(20000);
    }
//    window.trigger_game_loop();
}

void WaitingRoomThread::end_waiting() {
    end = true;
}

void WaitingRoomThread::send_new_teammates(std::vector<std::string> &new_teammates) {
    for (auto const &it : new_teammates) {
        if (std::find(teammates.begin(), teammates.end(), it) ==
            teammates.end()) {
            std::cout << it << std::endl;
            window.new_player(it);
        }
    }
}
WaitingRoomThread::~WaitingRoomThread() {}
