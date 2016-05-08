#include <vector>

#include "Match.h"

Player::~Player() {}

Host::~Host() {}

Match::Match(std::vector<Communicator*>& communicators) :
    communicators(communicators) {}

bool Match::started() {
    //TODO
    return false;
}

bool Match::has_host() {
    return this->communicators.size() > 0;
}

void Match::new_player_notification() {
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        this->communicators[i]->send_new_player_notification();
}

void Match::add_player(int fd) {
    this->communicators.push_back(new Communicator(fd));
    if (!this->has_host()) {
        this->players.push_back(new Host());
    } else {
        this->players.push_back(new Player());
        this->new_player_notification();
    }
}

Match::~Match() {
    for (unsigned int i = 0; i < this->players.size(); ++i)
        delete this->players[i];
}