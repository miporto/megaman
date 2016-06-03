#include <vector>
#include <iostream>

#include "Movable.h"

#define DIRECTION_POS 2

Movable::Movable(const std::vector<int>& position, const int velocity)
        : GameObject(position),
          direction(position[DIRECTION_POS]), velocity(velocity),
          current_vel_x(0), current_vel_y(0) {}

Movable::Movable(const int x, const int y,
                 const int direction, const int velocity)
        : GameObject(x, y), direction(direction), velocity(velocity) {}

void Movable::reset_position() {
    this->position.reset();
}

void Movable::change_x_movement(bool start, bool forward) {
    if (start)
        this->current_vel_x = this->velocity;
    else
        this->current_vel_x = 0;
    if (forward)
        this->position.forward();
    else
        this->position.backward();
}

void Movable::change_y_movement(bool start, bool forward) {
    if (start)
        this->current_vel_y = this->velocity;
    else
        this->current_vel_y = 0;
    if (forward)
        this->position.forward();
    else
        this->position.backward();
}

void Movable::move() {
    this->position.move(this->current_vel_x, this->current_vel_y);
}

std::vector<int> Movable::get_position() {
    std::vector<int> position = GameObject::get_position();
    position.push_back(this->direction);
    return position;
}

Movable::~Movable() {}
