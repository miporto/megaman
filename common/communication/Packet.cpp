#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "Packet.h"

#define PRESSED_CODE 1
#define RELEASED_CODE 0

Packet::~Packet() {}

NewPlayer::NewPlayer(const std::string name) : name(name) {}

const std::string NewPlayer::get_name() const { return this->name; }

char NewPlayer::get_id() const { return this->id; }

std::string NewPlayer::get_str() const {
    std::string str;

    str.push_back(this->id);

    int len = this->name.length();
    char* len_arr = (char*)&len;
    str.push_back(len_arr[0]);
    str.push_back(len_arr[1]);
    str.push_back(len_arr[2]);
    str.push_back(len_arr[3]);

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

StageInfo::StageInfo(const std::string& stage_info)
        : stage_info(stage_info) {}

char StageInfo::get_id() const { return this->id; }

std::string StageInfo::get_str() const {
    std::string str;

    str.push_back(this->id);

    int len = this->stage_info.length();
    char* len_arr = (char*)&len;
    str.push_back(len_arr[0]);
    str.push_back(len_arr[1]);
    str.push_back(len_arr[2]);
    str.push_back(len_arr[3]);

    str.append(this->stage_info);

    return str;
}

const std::string& StageInfo::get_info() const {
    return this->stage_info;
}

StageInfo::~StageInfo() {}

Update::Update(const std::string& name, const std::string& update_info)
        : name(name), update_info(update_info) {}

char Update::get_id() const { return this->id; }

const std::string& Update::get_name() const { return this->name; }

std::string Update::get_str() const {
    std::string str;

    str.push_back(this->id);

    int name_len = this->name.length();
    char* len_arr = (char*)&name_len;
    str.push_back(len_arr[0]);
    str.push_back(len_arr[1]);
    str.push_back(len_arr[2]);
    str.push_back(len_arr[3]);

    str.append(this->name);

    int len_update = this->update_info.length();
    len_arr = (char*)&len_update;
    str.push_back(len_arr[0]);
    str.push_back(len_arr[1]);
    str.push_back(len_arr[2]);
    str.push_back(len_arr[3]);

    str.append(this->update_info);

    return str;
}

const std::string& Update::get_update_info() const {
    return this->update_info;
}

Update::~Update() {}

Deceased::Deceased(const int object_id) : object_id(object_id) {}

char Deceased::get_id() const { return this->id; }

std::string Deceased::get_str() const {
    std::string str;

    str.push_back(this->id);

    char* id_arr = (char*)&this->object_id;
    str.push_back(id_arr[0]);
    str.push_back(id_arr[1]);
    str.push_back(id_arr[2]);
    str.push_back(id_arr[3]);

    return str;
}

int Deceased::get_object_id() const { return this->object_id; }

Deceased::~Deceased() { }

Action::Action(const std::string& name,
               const char action_id, const bool pressed)
        : name(name), action_id(action_id), pressed(pressed) {
    std::cout << "Action name: " << name << std::endl;
}

Action::Action(const std::string& name,
               const char action_id, const char pressed)
        : name(name), action_id(action_id), pressed(pressed) {
    std::cout << "Action name: " << name << std::endl;
}

char Action::get_id() const { return this->id; }

char Action::get_action() const { return this->action_id; }

const std::string& Action::get_name() const { return this->name; }

bool Action::is_pressed() const { return this->pressed != 0; }

std::string Action::get_str() const {
    std::string str;
    str.push_back(this->id);

    int len = this->name.length();
    char* len_arr = (char*)&len;
    str.push_back(len_arr[0]);
    str.push_back(len_arr[1]);
    str.push_back(len_arr[2]);
    str.push_back(len_arr[3]);

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
