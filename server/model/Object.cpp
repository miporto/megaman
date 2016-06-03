#include <string>
#include <vector>

#include "Object.h"
#include "MegaMan.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1

Object::Object(const std::string& name, const std::vector<int>& position)
        : GameObject(position), name(name) {}

const std::string& Object::get_name() { return this->name; }

void Object::collide_with(Enemy* enemy) {}

void Object::collide_with(Object* object) {}

void Object::collide_with(Projectile* projectile) {}

void Object::execute_collision_with(GameObject* other) {
    other->collide_with(this);
}

void Object::tick() {}

std::string Object::info() { return ""; }

bool Object::is_dead() { return false; }

Object::~Object() {}

Stairs::Stairs(const std::vector<int>& position) :
        Object(STAIRS_NAME, position) {}

void Stairs::collide_with(MegaMan* mm) {
    //TODO Cuando mm esta encima, se puede
    // mover verticalmente sin limitaciones
}

Stairs::~Stairs() {}

Spike::Spike(const std::vector<int>& position) :
        Object(SPIKE_NAME, position) {}

void Spike::collide_with(MegaMan* mm) { mm->kill(); }

Spike::~Spike() {}

Block::Block(const std::vector<int>& position) :
        Object(BLOCK_NAME, position) {}

void Block::collide_with(MegaMan* mm) { mm->correct_position(); }

Block::~Block() {}

Cliff::Cliff(const std::vector<int>& position) :
        Object(CLIFF_NAME, position) {}

void Cliff::collide_with(MegaMan* mm) { mm->kill(); }

Cliff::~Cliff() {}
