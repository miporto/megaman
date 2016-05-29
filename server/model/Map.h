#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

#include "Enemy.h"
#include "Object.h"
#include "Player.h"

class Map {
    private:
        //b2Vec2 gravity;
        //b2World world;
        const unsigned int width, height;

        std::vector<Player*> players;
        std::vector<Object*> objects;
        std::vector<Enemy*> enemies;
        std::vector<Projectile*> projectiles;

    public:
        Map();
        void add_player(Player* player);
        void set(const std::string& info);
        void tick();
        void get_rid_of_corpses();
        const std::string status();
        ~Map();
};

#endif //MAP_H
