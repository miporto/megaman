#include "Stage.h"

StageIDProtected::StageIDProtected() : stage_id(0) {}

void StageIDProtected::set_id(char stage_id) {
    Lock l(this->m);
    this->stage_id = stage_id;
}

char StageIDProtected::operator()() {
    Lock l(this->m);
    return this->stage_id;
}

StageIDProtected::~StageIDProtected() {}

StageFactory::StageFactory(char id) : id(id) {}

StageFactory::~StageFactory() {}

Stage::Stage(char id, std::vector<Player*>& players) : factory(id), players(players) {}

Stage::~Stage() {}