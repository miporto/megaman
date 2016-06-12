#include <string>
#include <utility>

#include "server/communication/InfoMaker.h"
#include "GameObjectHandler.h"
#include "GameObjectSetter.h"

void GameObjectHandler::set(const std::string& info) {
    GameObjectSetter setter(info, this);
}

void GameObjectHandler::add_game_object(GameObject* object) {
    this->objects.push_back(object);
    this->object_id[object] = this->objects.size();
}

const std::string GameObjectHandler::status() {
    InfoMaker info;
    std::pair<std::string, std::string> status;
    for (unsigned int i = 0; i < this->objects.size(); ++i) {
        status = this->objects[i]->info(this->object_id[this->objects[i]]);
        info.add(status.first, status.second);
    }
    return info.str();
}

void GameObjectHandler::tick() {
    for (unsigned int i = 0; i < this->objects.size(); ++i)
        this->objects[i]->tick();
}

GameObjectHandler::~GameObjectHandler() {
    for (unsigned int i = 0; i < this->objects.size(); ++i)
        if (!this->objects[i]->is_megaman()) delete this->objects[i];
}
