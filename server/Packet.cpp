#include <string>

#include "Packet.h"

Packet::Packet(char id) : id(id) { str.push_back(id); }

char Packet::get_id() const { return this->id; }

std::string Packet::get_str() const { return this->str; }

Packet::~Packet() {}

StagePick::StagePick(char id, char stage_id) : Packet(id), stage_id(stage_id) {
    str.push_back(id);
    str.push_back(stage_id);
}

char StagePick::get_stage_id() const {
    return this->stage_id;
}

std::string StagePick::get_str() const { return this->str; }

StagePick::~StagePick() {}

StageInfo::StageInfo(char id, char position) :
        Packet(id), type(0), position(position) {
    str.push_back(id);
    str.push_back(position);
}

StageInfo::StageInfo(char id, char type, char position) :
    Packet(id), type(type), position(position) {
    str.push_back(id);
    str.push_back(type);
    str.push_back(position);
}

std::string StageInfo::get_str() const {
    return this->str;
}

StageInfo::~StageInfo() {}

Packet* PacketsProtected::pop() {
    Lock l(this->m);
    Packet* packet = this->packets[0];
    this->packets.erase(this->packets.begin());
    return packet;
}

void PacketsProtected::push(Packet* packet) {
    Lock l(this->m);
    this->packets.push_back(packet);
}

bool PacketsProtected::is_empty() { return this->packets.size() == 0; }

PacketsProtected::~PacketsProtected() {
    for (unsigned int i = 0; i < this->packets.size(); ++i)
        delete this->packets[i];
}