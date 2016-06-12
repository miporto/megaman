#include <string>
#include <utility>

#include "server/communication/InfoMaker.h"
#include "GameObjectHandler.h"
#include "GameObjectSetter.h"
#include "Shooter.h"

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

void GameObjectHandler::check_collisions() {
    GameObject* current_object;
    for (unsigned int i = 0; i < this->objects.size(); ++i) {
        current_object = this->objects[i];
        for (unsigned int j = 0; j < this->objects.size(); ++j) {
            if (i == j) continue;
            if (current_object->collided_with(this->objects[j]))
                current_object->execute_collision_with(this->objects[j]);
        }
    }
}

void GameObjectHandler::create_new_projectiles() {
    for (unsigned int i = 0; i < this->objects.size(); ++i)
        if (this->objects[i]->shoots_per_tick())
            ((Shooter*)this->objects[i])->shoot(this);
}

GameObjectHandler::~GameObjectHandler() {
    for (unsigned int i = 0; i < this->objects.size(); ++i)
        if (!this->objects[i]->is_megaman()) delete this->objects[i];
}
