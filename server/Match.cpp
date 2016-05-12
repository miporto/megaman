#include <string>
#include <vector>

#include "Match.h"

#define PLAYERS_MAX 4

Match::Match(std::vector<Communicator*>& communicators)
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

void Match::new_player_notification() {
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        this->communicators[i]->send_new_player_notification();
}

void Match::add_player(int fd) {
    Lock l(this->m);
    if (this->is_full())
        throw MatchError("Mega Man Co-op match is full");
    if (this->has_started())
        throw MatchError("Mega Man Co-op match has already started");

    if (!this->has_host()) {
        HostCommunicator* hc = new HostCommunicator(fd, this->stage_id);
        hc->start();
        this->communicators.push_back(hc);
        this->players.push_back(new Host());

    } else {
        this->communicators.push_back(new Communicator(fd));
        this->players.push_back(new Player());
        this->new_player_notification();
    }
}

void Match::start_stage() {
    ((HostCommunicator*)this->communicators[0])->join();
    Stage stage(this->stage_id(), this->players);
    //TODO Continuar
}

Match::~Match() {
    for (unsigned int i = 0; i < this->players.size(); ++i)
        delete this->players[i];
}

MatchError::MatchError(const std::string error_msg) throw()
    : error_msg(error_msg) {}

const char* MatchError::what() const throw() { return error_msg.c_str(); }

MatchError::~MatchError() throw() {}
