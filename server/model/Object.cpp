#include <vector>

#include "Object.h"

Object::Object(const std::vector<int>& position) :
        position(position) {}

Object::~Object() {}

Stairs::Stairs(const std::vector<int>& position) :
        Object(position) {}

void Stairs::interact(MegaMan& mm) {
    //TODO Cuando mm esta encima, se puede
    // mover verticalmente sin limitaciones
}

Stairs::~Stairs() {}

Spike::Spike(const std::vector<int>& position) :
        Object(position) {}

void Spike::interact(MegaMan& mm) {
    if (this->position == mm.get_position())
        mm.kill();
}

Spike::~Spike() {}

Block::Block(const std::vector<int>& position) :
        Object(position) {}

void Block::interact(MegaMan& mm) {
    //TODO Cuando mm esta en una celda adyacente,
    // no se puede mover para ese lado
}

Block::~Block() {}

Cliff::Cliff(const std::vector<int>& position) :
        Object(position) {}

void Cliff::interact(MegaMan& mm) {
    if (this->position == mm.get_position())
        mm.kill();
}

Cliff::~Cliff() {}
