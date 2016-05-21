#include <vector>

#include "Map.h"

Cell::~Cell() {}

Map::Map() : cells(HEIGTH, std::vector<Cell>(WIDTH)) {}

Map::~Map() {}
