#include <string>
#include <vector>

#include "Object.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1

Object::Object(const std::string& name, const std::vector<int>& position)
        : GameObject(position), name(name) {}

const std::string& Object::get_name() { return this->name; }

void Object::tick() {}

std::string Object::info() { return ""; }

bool Object::is_dead() { return false; }

Object::~Object() {}

Stairs::Stairs(const std::vector<int>& position) :
        Object(STAIRS_NAME, position) {}

void Stairs::interact(MegaMan& mm) {
    //TODO Cuando mm esta encima, se puede
    // mover verticalmente sin limitaciones
}

Stairs::~Stairs() {}

Spike::Spike(const std::vector<int>& position) :
        Object(SPIKE_NAME, position) {}

void Spike::interact(MegaMan& mm) {
    const std::vector<int> obj_pos = this->get_position();
    const std::vector<int> mm_pos = mm.get_position();
    if (obj_pos[X_COORD_POS] == mm_pos[X_COORD_POS]
        && obj_pos[Y_COORD_POS] == mm_pos[Y_COORD_POS])
        mm.kill();
}

Spike::~Spike() {}

Block::Block(const std::vector<int>& position) :
        Object(BLOCK_NAME, position) {}

void Block::interact(MegaMan& mm) {
    //TODO Cuando mm esta en una celda adyacente,
    // no se puede mover para ese lado
}

Block::~Block() {}

Cliff::Cliff(const std::vector<int>& position) :
        Object(CLIFF_NAME, position) {}

void Cliff::interact(MegaMan& mm) {
    const std::vector<int> obj_pos = this->get_position();
    const std::vector<int> mm_pos = mm.get_position();
    if (obj_pos[X_COORD_POS] == mm_pos[X_COORD_POS]
        && obj_pos[Y_COORD_POS] == mm_pos[Y_COORD_POS])
        mm.kill();
}

Cliff::~Cliff() {}
