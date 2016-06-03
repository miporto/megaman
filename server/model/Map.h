#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

#include "Enemy.h"
#include "Object.h"
#include "MegaMan.h"
#include "GameObject.h"

class Map {
    private:
        const unsigned int width, height;
        std::vector<GameObject*> objects;

    public:
        Map();
        void set(const std::string& info);
        void add_game_object(GameObject* object);
        void tick();
        void check_collisions();
        void get_rid_of_corpses();
        void create_new_projectiles();
        const std::string status();
        ~Map();
};

#endif //MAP_H
