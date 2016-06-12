#ifndef MAP_H
#define MAP_H

#include <map>
#include <vector>
#include <string>
#include <utility>

#include "common/communication/Packet.h"
#include "GameObject.h"
#include "GameObjectHandler.h"

class Map : public GameObjectHandler {
    private:
        const unsigned int width, height;
//        std::vector<GameObject*> objects;
//        std::map<GameObject*, int> object_id;

    public:
        Map();
//        void set(const std::string& info);
//        void add_game_object(GameObject* object);
        void tick();
        void check_collisions();
        std::vector<int> get_rid_of_corpses();
        void create_new_projectiles();
//        const std::string status();
        std::vector<FloatUpdate*> updates();
        ~Map();
};

#endif //MAP_H
