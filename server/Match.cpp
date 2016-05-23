#include <string>
#include <vector>
#include <iostream>

#include "Match.h"

#define PLAYERS_MAX 4

Match::Match(std::vector<ServerCommunicator*>& communicators)
    : communicators(communicators) {}

bool Match::has_started() {
    Lock l(this->m);
    return this->stage_id() != 0;
}

bool Match::is_full() {
    Lock l(this->m);
    return this->communicators.size() >= PLAYERS_MAX;
}

bool Match::has_host() { return this->communicators.size() > 0; }

void Match::send_new_player_notification(std::string& name) {
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        this->communicators[i]->send_new_player_notification(name);
}

void Match::send_stage_info(StageInfo* info) {
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        this->communicators[i]->send_screen_info(info);
}

void Match::add_player(int fd) {
    Lock l(this->m);

    if (this->communicators.size() >= PLAYERS_MAX)
        throw MatchError("Mega Man Co-op match is full");
    if (this->stage_id() != 0)
        throw MatchError("Mega Man Co-op match has already started");

    if (!this->has_host()) {
        HostCommunicator* hc = new HostCommunicator(fd, this->stage_id);
        std::string name = hc->receive_name();
        std::cout << "Host name: " << name << std::endl;
        hc->start();
        this->communicators.push_back(hc);
        this->game.new_player(name);

    } else {
        ServerCommunicator* c = new ServerCommunicator(fd);
        std::string name = c->receive_name();
        std::cout << "Player name: " << name << std::endl;
        this->communicators.push_back(c);
        this->game.new_player(name);
        this->send_new_player_notification(name);
    }
}

void Match::start_stage() {
    ((HostCommunicator*)this->communicators[0])->join();
    char stage_id = this->stage_id();

    StageInfo* info = StageFactory::stage_info(stage_id);

    this->send_stage_info(info);
    this->game.start_stage(info);

    //TODO continuara

    delete info;
}

Match::~Match() {}

MatchError::MatchError(const std::string error_msg) throw()
        : error_msg(error_msg) {}

const char* MatchError::what() const throw() { return error_msg.c_str(); }

MatchError::~MatchError() throw() {}
