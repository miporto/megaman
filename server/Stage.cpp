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

Stage::Stage(std::vector<Player*>& players) : id(0), players(players) {}

bool Stage::has_started() {
    return this->id != 0;
}

void Stage::operator()(char id) {
    this->id = id;
    //Armar el Stage correspondiente al numero que le llega
    //probablemente instanciando una StageFactory?
}

Stage::~Stage() {}