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
        ~Cell();
};

class Map {
    private:
        std::vector<std::vector<Cell*>> cells;
    public:
        Map();
        void set(StageInfo* info);
        ~Map();
};

#endif //MAP_H
