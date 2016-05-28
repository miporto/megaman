#ifndef MAP_H
#define MAP_H

#include <vector>
//#include <extern/Box2D/Box2D.h>

#include "Enemy.h"
#include "Object.h"

class Cell {
    private:
        std::vector<Object*> objects;
        std::vector<Enemy*> enemies;
        std::vector<Projectile*> projectiles;
    public:
        void add(Enemy* object);
        void add(Object* object);
        void add(Projectile* projectile);
        std::vector<Enemy*>& get_enemies();
        std::vector<Projectile*>& get_projectiles();
        void get_rid_of_corpses();
        ~Cell();
};

class Map {
    private:
        //b2Vec2 gravity;
        //b2World world;
        const unsigned int width, height;

        std::vector<std::vector<Cell*>> cells;

        void tick_enemies_on_cell(Cell* cell);
        void tick_projectiles_on_cell(Cell* cell);

    public:
        Map();
        void set(StageInfo* info);
        void tick();
        void get_rid_of_corpses();
        ~Map();
};

#endif //MAP_H
