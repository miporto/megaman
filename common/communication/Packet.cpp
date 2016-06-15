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

    int name_len = this->name.length();
    char* len_arr = (char*)&name_len;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(len_arr[i]);

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
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(len_arr[i]);

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
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(len_arr[i]);

    str.append(this->name);

    int len_update = this->update_info.length();
    len_arr = (char*)&len_update;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(len_arr[i]);

    str.append(this->update_info);

    return str;
}

const std::string& Update::get_update_info() const {
    return this->update_info;
}

Update::~Update() {}

FloatUpdate::FloatUpdate(const std::string& name, const int object_id,
                         const float x, const float y)
        : name(name), object_id(object_id), x(x), y(y) {}

char FloatUpdate::get_id() const { return this->id; }

const std::string& FloatUpdate::get_name() const { return this->name; }

int FloatUpdate::get_object_id() const { return this->object_id; }

float FloatUpdate::get_x() const { return this->x; }

float FloatUpdate::get_y() const { return this->y; }

std::string FloatUpdate::get_str() const {
    std::string str;

    str.push_back(this->id);

    int name_len = this->name.length();
    char* len_arr = (char*)&name_len;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(len_arr[i]);

    str.append(this->name);

    char* object_id_arr = (char*)&this->object_id;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(object_id_arr[i]);

    char* x_arr = (char*)&this->x;
    for (unsigned int i = 0; i < sizeof(float); ++i)
        str.push_back(x_arr[i]);

    char* y_arr = (char*)&this->y;
    for (unsigned int i = 0; i < sizeof(float); ++i)
        str.push_back(y_arr[i]);

    return str;
}

FloatUpdate::~FloatUpdate() {}

MegaManFloatUpdate::MegaManFloatUpdate(const std::string& name,
                                       const std::string& player_name,
                                       const int object_id,
                                       const float x, const float y,
                                       const int direction_x,
                                       const int direction_y,
                                       const float energy)
        : FloatUpdate(name, object_id, x, y),
          player_name(player_name), energy(energy),
          direction_x(direction_x), direction_y(direction_y) {}

char MegaManFloatUpdate::get_id() const { return this->id; }

const std::string& MegaManFloatUpdate::get_player_name() const {
    return this->player_name;
}

float MegaManFloatUpdate::get_energy() const { return this->energy; }

int MegaManFloatUpdate::get_direction_x() const { return this->direction_x; }

int MegaManFloatUpdate::get_direction_y() const { return this->direction_y; }

std::string MegaManFloatUpdate::get_str() const {
    std::string str;

    str.push_back(this->id);

    int name_len = this->name.length();
    char* len_arr = (char*)&name_len;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(len_arr[i]);

    str.append(this->name);

    char* object_id_arr = (char*)&this->object_id;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(object_id_arr[i]);

    char* x_arr = (char*)&this->x;
    for (unsigned int i = 0; i < sizeof(float); ++i)
        str.push_back(x_arr[i]);

    char* y_arr = (char*)&this->y;
    for (unsigned int i = 0; i < sizeof(float); ++i)
        str.push_back(y_arr[i]);

    int player_name_len = this->player_name.length();
    char* player_len_arr = (char*)&player_name_len;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(player_len_arr[i]);

    str.append(this->player_name);

    char* energy_arr = (char*)&this->energy;
    for (unsigned int i = 0; i < sizeof(float); ++i)
        str.push_back(energy_arr[i]);

    char* dir_x_arr = (char*)&this->direction_x;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(dir_x_arr[i]);

    char* dir_y_arr = (char*)&this->direction_y;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(dir_y_arr[i]);

    return str;
}

MegaManFloatUpdate::~MegaManFloatUpdate() {}

BossFloatUpdate::BossFloatUpdate(const std::string& name,
                                       const int object_id,
                                       const float x, const float y,
                                       const int direction_x,
                                       const int direction_y,
                                       const float energy)
        : FloatUpdate(name, object_id, x, y), energy(energy),
          direction_x(direction_x), direction_y(direction_y) {}

char BossFloatUpdate::get_id() const { return this->id; }

float BossFloatUpdate::get_energy() const { return this->energy; }

int BossFloatUpdate::get_direction_x() const { return this->direction_x; }

int BossFloatUpdate::get_direction_y() const { return this->direction_y; }

std::string BossFloatUpdate::get_str() const {
    std::string str;

    str.push_back(this->id);

    int name_len = this->name.length();
    char* len_arr = (char*)&name_len;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(len_arr[i]);

    str.append(this->name);

    char* object_id_arr = (char*)&this->object_id;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(object_id_arr[i]);

    char* x_arr = (char*)&this->x;
    for (unsigned int i = 0; i < sizeof(float); ++i)
        str.push_back(x_arr[i]);

    char* y_arr = (char*)&this->y;
    for (unsigned int i = 0; i < sizeof(float); ++i)
        str.push_back(y_arr[i]);

    char* energy_arr = (char*)&this->energy;
    for (unsigned int i = 0; i < sizeof(float); ++i)
        str.push_back(energy_arr[i]);

    char* dir_x_arr = (char*)&this->direction_x;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(dir_x_arr[i]);

    char* dir_y_arr = (char*)&this->direction_y;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(dir_y_arr[i]);

    return str;
}

BossFloatUpdate::~BossFloatUpdate() {}

Deceased::Deceased(const int object_id) : object_id(object_id) {}

char Deceased::get_id() const { return this->id; }

std::string Deceased::get_str() const {
    std::string str;

    str.push_back(this->id);

    char* object_id_arr = (char*)&this->object_id;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(object_id_arr[i]);

    return str;
}

int Deceased::get_object_id() const { return this->object_id; }

Deceased::~Deceased() {}

ChamberInfo::ChamberInfo(const std::string& chamber_info)
        : chamber_info(chamber_info) {}

char ChamberInfo::get_id() const { return this->id; }

std::string ChamberInfo::get_str() const {
    std::string str;

    str.push_back(this->id);

    int len = this->chamber_info.length();
    char* len_arr = (char*)&len;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(len_arr[i]);

    str.append(this->chamber_info);

    return str;
}

const std::string& ChamberInfo::get_info() const { return this->chamber_info; }

ChamberInfo::~ChamberInfo() {}

Action::Action(const std::string& name,
               const char action_id, const bool pressed)
        : name(name), action_id(action_id), pressed(pressed) {}

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

    int name_len = this->name.length();
    char* len_arr = (char*)&name_len;
    for (unsigned int i = 0; i < sizeof(int); ++i)
        str.push_back(len_arr[i]);

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
        throw PacketError("Action Packet does not belong in "
                                  "ReceivedPacketsProtected structure");
    else
        this->packets[packet->get_id()].push_back(packet);
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

PacketError::PacketError(const std::string error_msg) throw()
        : SystemError(error_msg) {}
