#ifndef MAP_H
#define MAP_H

#include <vector>

#include "Enemy.h"
#include "Object.h"

#define WIDTH 640
#define HEIGHT 480

class Cell {
    private:
        //vector de GameObject?
        //Padre de Enemy, MM, Object, Projectile y PowerUp?
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
