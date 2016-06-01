#include <vector>
#include <iostream>

#include "Movable.h"

Movable::Movable(const std::vector<int>& position, const int velocity)
        : GameObject(position), velocity(velocity) {}

Movable::Movable(const int x, const int y,
                 const int direction, const int velocity)
        : GameObject(x, y, direction), velocity(velocity) {}

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
