#include <string>
#include <vector>

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

void Match::send_stage_info(ScreenInfo* info) {
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        this->communicators[i]->send_screen_info(info);
}

void Match::add_player(int fd) {
    Lock l(this->m);

    if (this->is_full())
        throw MatchError("Mega Man Co-op match is full");
    if (this->has_started())
        throw MatchError("Mega Man Co-op match has already started");

    if (!this->has_host()) {
        HostCommunicator* hc = new HostCommunicator(fd, this->stage_id);
        std::string name = hc->receive_name();
        hc->start();
        this->communicators.push_back(hc);
        this->players.push_back(new Player(name));

    } else {
        ServerCommunicator* c = new ServerCommunicator(fd);
        std::string name = c->receive_name();
        this->communicators.push_back(c);
        this->players.push_back(new Player(name));
        this->send_new_player_notification(name);
    }
}

void Match::start_stage() {
    ((HostCommunicator*)this->communicators[0])->join();

    //TODO ver donde dejar referencia a la instancia de Stage
    Stage stage(this->stage_id(), this->players);

    ScreenInfo* info = stage.get_stage_info();
    this->send_stage_info(info);
    delete info;
}

Match::~Match() {
    for (unsigned int i = 0; i < this->players.size(); ++i)
        delete this->players[i];
}

MatchError::MatchError(const std::string error_msg) throw()
        : error_msg(error_msg) {}

const char* MatchError::what() const throw() { return error_msg.c_str(); }

MatchError::~MatchError() throw() {}
