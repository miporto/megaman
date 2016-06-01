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

        std::vector<MegaMan*> players;
        std::vector<Object*> objects;
        std::vector<Enemy*> enemies;
        std::vector<Projectile*> projectiles;

    public:
        Map();
        void add_player(MegaMan* player);
        void set(const std::string& info);
        void add_enemy(Enemy* enemy);
        void add_object(Object* object);
        void tick();
        void get_rid_of_corpses();
        const std::string status();
        ~Map();
};

#endif //MAP_H
