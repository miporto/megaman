#include <vector>

#include "Match.h"
#include "common/Socket.h"

Player::Player(int fd) : peer(fd) {}

Player::~Player() {
    this->peer.shutdown();
}

Host::Host(int fd) : Player(fd) {}

bool Host::waiting_for_players() {
    //TODO
    return true;
}

Host::~Host() {}

Match::Match(std::vector<Communicator>& communicators) :
    communicators(communicators) {}

bool Match::has_host() {
    return this->communicators.size() > 0;
}

Host* Match::host() {
    return (Host*)this->players[0];
}

bool Match::host_waiting() {
    if (this->has_host())
        return this->host()->waiting_for_players();
    return true;
}

void Match::add_player(int fd) {
    if (this->players.size() == 0) {
        this->players.push_back(new Host(fd));
    } else {
        this->players.push_back(new Player(fd));
    }
}

Match::~Match() {
    for (unsigned int i = 0; i < this->players.size(); ++i)
        delete this->players[i];
}
