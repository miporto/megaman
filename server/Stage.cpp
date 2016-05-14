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

StageFactory::StageFactory(char id) : id(id) {}

std::vector<char> StageFactory::positions_of_spawns
        (const int screen, const int enemy_id) {
    std::vector<char> positions;
    //TODO leer .JSON
    return positions;
}

std::vector<char> StageFactory::positions_of_objects
        (const int screen, const int object_id) {
    std::vector<char> positions;
    //TODO leer .JSON
    return positions;
}

ScreenInfo* StageFactory::screen_info(const int screen) {
    //TODO crean ScreenInfo con metodos anteriores
    return NULL;
}

StageFactory::~StageFactory() {}

Stage::Stage(char id, std::vector<Player*>& players) :
        factory(id), players(players), current_screen(0) {}

ScreenInfo* Stage::next_screen() {
    this->current_screen++;
    ScreenInfo* info = factory.screen_info(this->current_screen);
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
