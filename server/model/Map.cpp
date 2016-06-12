#include <utility>
#include <map>
#include <vector>
#include <string>

#include "server/communication/InfoMaker.h"
#include "Map.h"
#include "Factory.h"
#include "GameObjectSetter.h"
#include "Enemy.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1

Map::Map() : width(MapFactory::width()), height(MapFactory::height()) {}

//void Map::set(const std::string& info) {
//    GameObjectSetter setter(info, this);
//}

//void Map::add_game_object(GameObject* object) {
//    this->objects.push_back(object);
//    this->object_id[object] = this->objects.size();
//}

//void Map::tick() {
//    for (unsigned int i = 0; i < this->objects.size(); ++i)
//        this->objects[i]->tick();
//}

//void Map::check_collisions() {
//    GameObject* current_object;
//    for (unsigned int i = 0; i < this->objects.size(); ++i) {
//        current_object = this->objects[i];
//        for (unsigned int j = 0; j < this->objects.size(); ++j) {
//            if (i == j) continue;
//            if (current_object->collided_with(this->objects[j]))
//                current_object->execute_collision_with(this->objects[j]);
//        }
//    }
//}

std::vector<int> Map::get_rid_of_corpses() {
    std::vector<int> deceased;
    GameObject* dead_obj;
    for (unsigned int i = 0; i < this->objects.size(); ++i) {
        if (this->objects[i]->is_dead()) {
            dead_obj = this->objects[i];

            deceased.push_back(this->object_id[dead_obj]);

            this->object_id.erase(dead_obj);
            this->objects.erase(this->objects.begin() + i);
            if (!dead_obj->is_megaman()) delete dead_obj;
        }
    }

    return deceased;
}

void Map::create_new_projectiles() {
    for (unsigned int i = 0; i < this->objects.size(); ++i)
        if (this->objects[i]->shoots_per_tick())
            ((Enemy*)this->objects[i])->shoot(this);
}

//const std::string Map::status() {
//    InfoMaker info;
//    std::pair<std::string, std::string> status;
//    for (unsigned int i = 0; i < this->objects.size(); ++i) {
//        status = this->objects[i]->info(this->object_id[this->objects[i]]);
//        info.add(status.first, status.second);
//    }
//    return info.str();
//}

std::vector<FloatUpdate*> Map::updates() {
    std::vector<FloatUpdate*> updates;
    for (unsigned int i = 0; i < this->objects.size(); ++i)
        if (this->objects[i]->it_moved())
            updates.push_back(this->objects[i]->update
                    (this->object_id[this->objects[i]]));
    return updates;
}

Map::~Map() {}
