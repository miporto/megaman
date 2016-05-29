#include <vector>

#include "Movable.h"

Movable::Movable(const std::vector<int>& position, const int velocity)
        : position(position), velocity(velocity) {}

Movable::Movable(const int x, const int y,
                 const int direction, const int velocity)
        : position(x, y, direction), velocity(velocity) {}

std::vector<int> Movable::get_position() {
    return this->position.get_position();
}

void Movable::reset_position() {
    this->position.reset();
}

void Movable::move(int amount_x, int amount_y) {
    this->position.move(this->velocity * amount_x,
                        this->velocity * amount_y);
}

void Movable::change_direction() {
    this->position.change_direction();
}

Movable::~Movable() {}
