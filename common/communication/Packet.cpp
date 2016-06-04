#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "Packet.h"

#define PRESSED_CODE 1
#define RELEASED_CODE 0

Packet::~Packet() {}

NewPlayer::NewPlayer(const std::string name) :
        name(name.substr(0, NAME_LENGTH)) {
    for (size_t i = name.size(); i < NAME_LENGTH; ++i)
        this->name.push_back('\0');
}

const std::string NewPlayer::get_name() const { return this->name; }

char NewPlayer::get_id() const { return this->id; }

std::string NewPlayer::get_str() const {
    std::string str;
    str.push_back(this->id);
    str.append(this->name);
    return str;
}

NewPlayer::~NewPlayer() {}

StagePick::StagePick(const char stage_id) : stage_id(stage_id) {}

char StagePick::get_stage_id() const { return this->stage_id; }

char StagePick::get_id() const { return this->id; }

std::string StagePick::get_str() const {
    std::string str;
    str.push_back(this->id);
    str.push_back(this->stage_id);
    return str;
}

StagePick::~StagePick() {}

Stage::Stage(const std::string& stage_info)
        : length(stage_info.size()), stage_info(stage_info) {}

char Stage::get_id() const { return this->id; }

std::string Stage::get_str() const {
    std::string str;
    str.push_back(this->id);
    str.append((char*)this->length);
    str.append(this->stage_info);
    return str;
}

std::string Stage::get_info() const {
    std::string info;
    info.append(this->stage_info);
    return info;
}

Stage::~Stage() {}

Action::Action(const std::string& name,
               const char action_id, const bool pressed)
        : name(name.substr(0, NAME_LENGTH)),
          action_id(action_id),
          pressed(pressed) {
    for (size_t i = name.size(); i < NAME_LENGTH; ++i)
        this->name.push_back('\0');
}

Action::Action(const std::string& name,
               const char action_id, const char pressed)
        : name(name), action_id(action_id), pressed(pressed) {}

char Action::get_id() const { return this->id; }

char Action::get_action() const { return this->action_id; }

const std::string& Action::get_name() const { return this->name; }

bool Action::is_pressed() const { return this->pressed != 0; }

std::string Action::get_str() const {
    std::string str;
    str.push_back(this->id);
    str.append(this->name);
    str.push_back(this->action_id);
    if (pressed)
        str.push_back(PRESSED_CODE);
    else
        str.push_back(RELEASED_CODE);
    return str;
}

Action::~Action() {}

Right::Right(const std::string& name, const bool pressed)
        : Action(name, RIGHT, pressed) {}

Left::Left(const std::string& name, const bool pressed)
        : Action(name, LEFT, pressed) {}

Up::Up(const std::string& name, const bool pressed)
        : Action(name, UP, pressed) {}

Shoot::Shoot(const std::string& name, const bool pressed)
        : Action(name, SHOOT, pressed) {}

bool PacketsQueueProtected::is_empty() {
    Lock l(this->m);
    return this->packets.size() == 0;
}

Packet* PacketsQueueProtected::pop() {
    Lock l(this->m);
    Packet* packet = this->packets[0];
    this->packets.erase(this->packets.begin());
    return packet;
}

void PacketsQueueProtected::push(Packet* packet) {
    Lock l(this->m);
    this->packets.push_back(packet);
}

PacketsQueueProtected::~PacketsQueueProtected() {
    for (unsigned int i = 0; i < this->packets.size(); ++i)
        delete this->packets[i];
}

bool ReceivedPacketsProtected::is_empty(const char id) {
    Lock l(this->m);
    return this->packets[id].size() == 0;
}

Packet* ReceivedPacketsProtected::pop(const char id) {
    Lock l(this->m);
    Packet* packet = this->packets[id][0];
    this->packets[id].erase(this->packets[id].begin());
    return packet;
}

void ReceivedPacketsProtected::push(Packet* packet) {
    Lock l(this->m);
    if (packet->get_id() == ACTION)
        this->actions.push(packet);
    else
        this->packets[packet->get_id()].push_back(packet);
}

PacketsQueueProtected* ReceivedPacketsProtected::get_actions() {
    return &(this->actions);
}

ReceivedPacketsProtected::~ReceivedPacketsProtected() {
    typedef std::map<char, std::vector<Packet*>>::iterator it_packets;
    for (it_packets iterator = this->packets.begin();
        iterator != this->packets.end();
        ++iterator)
        for (unsigned int i = 0;
             i < this->packets[iterator->first].size();
             ++i)
            delete this->packets[iterator->first][i];
}
