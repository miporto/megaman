#include <vector>
#include <string>
#include <server/communication/TickInfoMaker.h>

#include "Map.h"
#include "Factory.h"
#include "ServerStageSetter.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1

Map::Map() : width(MapFactory::width()), height(MapFactory::height()) {}

void Map::set(const std::string& info) {
    ServerStageSetter setter(info, this);
}

void Map::add_game_object(GameObject* object) {
    this->objects.push_back(object);
}

void Map::tick() {
    for (unsigned int i = 0; i < this->objects.size(); ++i)
        this->objects[i]->tick();
}

void Map::get_rid_of_corpses() {
    //TODO que no se eliminen jugadores
    GameObject* dead_obj;
    for (unsigned int i = 0; i < this->objects.size(); ++i) {
        if (this->objects[i]->is_dead()) {
            dead_obj = this->objects[i];
            this->objects.erase(this->objects.begin() + i);
            delete dead_obj;
        }
    }
}

void Map::check_collisions() {
    //GameObject* current_object;
    for (unsigned int i = 0; i < this->objects.size(); ++i) {
        //current_object = this->objects[i];
        for (unsigned int j = 0; j < this->objects.size(); ++j) {
            //TODO if (current_object.position == this->objects[j].position)
                //Guarda que puede ser el mismo
        }
    }
}

const std::string Map::status() {
    TickInfoMaker info;
    for (unsigned int i = 0; i < this->objects.size(); ++i)
        info.add(this->objects[i]->get_name(), this->objects[i]->info());
    return info.str();
}

Map::~Map() {
    //TODO que no se eliminen jugadores
    for (unsigned int i = 0; i < this->objects.size(); ++i)
        delete this->objects[i];
}
