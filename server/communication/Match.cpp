#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "server/model/Player.h"
#include "server/model/BossChamber.h"
#include "server/model/Factory.h"

#include "Match.h"

#define PLAYERS_MAX 4

Match::Match(std::vector<ServerCommunicator*>& communicators)
    : communicators(communicators) {
    this->stages[BOMBMAN] = StageFactory::initial_stage(BOMBMAN);
    this->stages[SPARKMAN] = StageFactory::initial_stage(SPARKMAN);
    this->stages[FIREMAN] = StageFactory::initial_stage(FIREMAN);
    this->stages[RINGMAN] = StageFactory::initial_stage(RINGMAN);
    //this->stages[MAGNETMAN] = StageFactory::initial_stage(MAGNETMAN);
}

bool Match::has_started() {
    Lock l(this->m);
    if (this->has_host())
        return this->host_communicator()->check_stage_id() != 0;
    return 0;
}

bool Match::is_full() {
    Lock l(this->m);
    return this->communicators.size() >= PLAYERS_MAX;
}

bool Match::ended() {
    return this->stages.size() == 0;
}

bool Match::has_host() { return this->communicators.size() > 0; }

HostCommunicator* Match::host_communicator() {
    return (HostCommunicator*)this->communicators[0];
}

void Match::notify_team_to_new_player(ServerCommunicator* new_comm) {
    for (unsigned int i = 0; i < this->communicators.size() - 1; ++i)
        new_comm->send_new_player_notification(this->communicators[i]->name());
}

void Match::notify_new_player_to_team(ServerCommunicator* new_comm) {
    for (unsigned int i = 0; i < this->communicators.size() - 1; ++i)
        this->communicators[i]->send_new_player_notification(new_comm->name());
}

void Match::notify_stage_pick_to_team(const char stage_id) {
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        this->communicators[i]->send_stage_pick(stage_id);
}

void Match::notify_stage_info(const std::string& info) {
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        this->communicators[i]->send_stage_info(info);
}

void Match::notify_boss_chamber_info(const std::string& info) {
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        this->communicators[i]->send_boss_chamber_info(info);
}

void Match::add_player(Socket* peer) {
    Lock l(this->m);

    if (this->communicators.size() >= PLAYERS_MAX)
        throw MatchError("Mega Man Co-op match is full");
    if (this->has_host() && this->host_communicator()->check_stage_id() != 0)
        throw MatchError("Mega Man Co-op match has already started");

    if (!this->has_host()) {
        HostCommunicator* hc = new HostCommunicator(peer, events);
        this->communicators.push_back(hc);
        hc->receive_name();

    } else {
        ServerCommunicator* c = new ServerCommunicator(peer, events);
        this->communicators.push_back(c);
        c->receive_name();

        this->notify_team_to_new_player(c);
        this->notify_new_player_to_team(c);
    }
}

void Match::play_stage(bool* exit) {
    const char stage_id = this->host_communicator()->receive_stage_id();
    const std::string& stage_info = this->stages[stage_id];

    if (stage_info.empty()) throw MatchError("Stage is unavaiable");

    this->notify_stage_pick_to_team(stage_id);

    Stage stage(this, this->communicators, this->events, stage_info);
    stage.run(exit);
    if (stage.beated()) {
        BossChamber chamber(this, this->communicators, this->events, stage_id);
        chamber.run(exit);
        if (chamber.beated()) {
            chamber.reward_players();
            this->stages.erase(stage_id);
        }
    }

    this->host_communicator()->reset_stage_id();
}

void Match::notify_deceased(const int object_id) {
    for (unsigned int i = 0; i < this->communicators.size(); ++i) {
        this->communicators[i]->send_deceased_info(object_id);
    }
}

void Match::notify_tick(const std::string& name, const std::string& tick_info) {
    for (unsigned int i = 0; i < this->communicators.size(); ++i) {
        this->communicators[i]->send_tick_info(name, tick_info);
    }
}

void Match::notify_tick(FloatUpdate* update) {
    for (unsigned int i = 0; i < this->communicators.size(); ++i)
        this->communicators[i]->send_tick_info(update);
}

Match::~Match() {}

MatchError::MatchError(const std::string error_msg) throw()
        : SystemError(error_msg) {}
