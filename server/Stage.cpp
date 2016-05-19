#include <vector>

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

std::vector<char> StageFactory::positions_of_spawns
        (const int stage_id, const int enemy_id) {
    std::vector<char> positions;
    //TODO leer .JSON
    return positions;
}

std::vector<char> StageFactory::positions_of_objects
        (const int stage_id, const int object_id) {
    std::vector<char> positions;
    //TODO leer .JSON
    return positions;
}

ScreenInfo* StageFactory::operator()(const int stage_id) {
    //TODO crean ScreenInfo con metodos anteriores
    return NULL;
}

StageFactory::~StageFactory() {}

Stage::Stage(char id, std::vector<Player*>& players) :
        id(id), players(players) {}

ScreenInfo* Stage::get_stage_info() {
    StageFactory factory;
    ScreenInfo* info = factory(this->id);
    //TODO Actualizar vector de enemigos
    //TODO Actualizar vector de objetos
    return info;
}

Stage::~Stage() {
    for (unsigned int i = 0; i < this->enemies.size(); ++i)
        delete this->enemies[i];
    for (unsigned int i = 0; i < this->objects.size(); ++i)
        delete this->objects[i];
}
