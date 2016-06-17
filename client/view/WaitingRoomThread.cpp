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
    std::vector<std::string> new_teammates = client.get_teammates();
    if (new_teammates.size() != teammates.size()) {
        //TODO: send all names of the teammates.
    }
}

void WaitingRoomThread::send_teammates() {
}
WaitingRoomThread::~WaitingRoomThread() {}
