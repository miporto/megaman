#include "Object.h"

Object::Object(const int x, const int y) :
        position(x, y) {}

Object::~Object() {}

Stairs::Stairs(const int x, const int y) :
        Object(x, y) {}

void Stairs::interact(MegaMan& mm) {
    //TODO
    //if (this->position == mm.get_position())
    //    mm.enable_vertical_movement();
}

Stairs::~Stairs() {}

Spike::Spike(const int x, const int y) :
        Object(x, y) {}

void Spike::interact(MegaMan& mm) {
    if (this->position == mm.get_position())
        mm.kill();
}

Spike::~Spike() {}

Block::Block(const int x, const int y) :
        Object(x, y) {}

void Block::interact(MegaMan& mm) {
    //TODO
}

Block::~Block() {}

Cliff::Cliff(const int x, const int y) :
        Object(x, y) {}

void Cliff::interact(MegaMan& mm) {
    if (this->position == mm.get_position())
        mm.kill();
}

Cliff::~Cliff() {}
