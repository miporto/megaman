#ifndef MAP_H
#define MAP_H

#include <vector>

#define WIDTH 640
#define HEIGTH 480

class Cell {
    private:
        //vector de GameObject? Padre de Enemy, MM, Object, Projectile y PowerUp
    public:
        ~Cell();
};

class Map {
    private:
        std::vector<std::vector<Cell>> cells;
    public:
        Map();
        ~Map();
};

#endif //MAP_H
