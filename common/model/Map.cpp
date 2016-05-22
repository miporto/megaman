#include <vector>

#include "common/StageInfo.h"
#include "Map.h"

void Cell::add(Enemy* enemy) {
    this->enemies.push_back(enemy);
}

void Cell::add(Object* object) {
    this->objects.push_back(object);
}

Cell::~Cell() {
    for (unsigned int i = 0; i < this->enemies.size(); ++i)
        delete this->enemies[i];
    for (unsigned int i = 0; i < this->objects.size(); ++i)
        delete this->objects[i];
}

Map::Map() : cells(HEIGTH, std::vector<Cell>(WIDTH)) {}

void Map::set(StageInfo* info) {
    //TODO Crear vector enemigos y objetos
    //Para los enemigos, que otros datos necesito?
    // velocidad
    // cantidad de vida
}

Map::~Map() {}
