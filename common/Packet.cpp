#include <string>

#include "common/Packet.h"

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

StageElement::StageElement(Position* position) : type(0), position(position) {}

StageElement::StageElement(const char type, Position* position) :
        type(type), position(position) {}

char StageElement::get_id() const { return this->id; }

char StageElement::get_type() const { return this->type; }

Position* StageElement::get_position() const {
    Position* position_clone = this->position->clone();
    return position_clone;
}

std::string StageElement::get_str() const {
    std::string str;
    str.push_back(this->id);
    str.push_back(this->type);
    str.append(this->position->str());
    return str;
}

StageElement::~StageElement() {
    delete this->position;
}

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
