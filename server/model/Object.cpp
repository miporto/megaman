#include <utility>
#include <string>
#include <vector>

#include "common/communication/Packet.h"
#include "Object.h"
#include "MegaMan.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1

#define OBJECT_SIDE 1

Object::Object(const std::string& name, const std::vector<float>& position)
        : GameObject(position, OBJECT_SIDE), name(name) {}

const std::string& Object::get_name() { return this->name; }

void Object::collide_with(Enemy* enemy) {}

void Object::collide_with(Object* object) {}

void Object::collide_with(Projectile* projectile) {}

void Object::collide_with(Boss* boss) {}

void Object::execute_collision_with(GameObject* other) {
    other->collide_with(this);
}

void Object::tick() {}

std::pair<std::string, std::string> Object::info(const int id) {
    std::vector<float> pos = this->get_position();
    std::stringstream sx;
    sx << pos[X_COORD_POS];
    std::stringstream sy;
    sy << pos[Y_COORD_POS];

    json info = { {"x", sx.str()},
                  {"y", sy.str()},
                  {"id", id} };
    return std::make_pair(this->get_name(), info.dump());
}

FloatUpdate* Object::update(const int id) {
    std::vector<float> pos = this->get_position();
    return new FloatUpdate(this->name, id, pos[X_COORD_POS], pos[Y_COORD_POS]);
}

bool Object::is_dead() { return false; }

Object::~Object() {}

Stairs::Stairs(const std::vector<float>& position) :
        Object(STAIRS_NAME, position) {}

void Stairs::collide_with(MegaMan* mm) {
    mm->standing_on_stairs();
}

Stairs::~Stairs() {}

Spike::Spike(const std::vector<float>& position) :
        Object(SPIKE_NAME, position) {}

void Spike::collide_with(MegaMan* mm) { mm->kill(); }

Spike::~Spike() {}

Block::Block(const std::vector<float>& position) :
        Object(BLOCK_NAME, position) {}

void Block::collide_with(MegaMan* mm) {
    mm->correct_position(this->get_position(), this->get_side());
}

Block::~Block() {}

Cliff::Cliff(const std::vector<float>& position) :
        Object(CLIFF_NAME, position) {}

void Cliff::collide_with(MegaMan* mm) { mm->kill(); }

Cliff::~Cliff() {}

Door::Door(const std::vector<float>& position) :
        Object(DOOR_NAME, position) {}

void Door::collide_with(MegaMan* mm) {
    throw ObjectError("Exit reached");
}

Door::~Door() {}

ObjectError::ObjectError(const std::string error_msg) throw()
        : SystemError(error_msg) {}
