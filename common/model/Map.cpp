#include <vector>

#include "Map.h"

bool Cell::add(GameObject* object) {
    for (unsigned int i = 0; i < this->objects.size(); ++i)
        this->objects[i]->can_step_on()
}

Cell::~Cell() {
    //TODO eliminar todos los GameObjects???
    // o se eliminan donde se crearon
}

Map::Map() : cells(HEIGTH, std::vector<Cell>(WIDTH)) {}

Map::~Map() {}
