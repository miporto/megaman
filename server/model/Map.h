#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <Box2D/Box2D.h>

#include "Enemy.h"
#include "Object.h"
#include "Player.h"
#include "GameObject.h"

class Map {
    private:
        b2Vec2 gravity;
        b2World world;
        const unsigned int width, height;

        std::vector<Player*> players;
        std::vector<Object*> objects;
        std::vector<Enemy*> enemies;
        std::vector<Projectile*> projectiles;

        void add_body(GameObject* object);

    public:
        Map();
        void add_player(Player* player);
        void set(const std::string& info);
        void add_enemy(Enemy* enemy);
        void add_object(Object* object);
        void tick();
        void get_rid_of_corpses();
        const std::string status();
        ~Map();
};

#endif //MAP_H
