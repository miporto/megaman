#include <vector>

#include "serverMatch.h"
#include "commonSocket.h"

Player::Player(int fd) : peer(fd) {}

Player::~Player() {}

Host::Host(int fd) : Player(fd) {}

Host::~Host() {}

Host* Match::host() {
    return (Host*)this->players[0];
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
