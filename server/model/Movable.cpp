#include <vector>
#include <iostream>

#include "Movable.h"

#define DIRECTION_POS 2

#define FORWARD 1
#define BACKWARD -1

Movable::Movable(const std::vector<int>& position, const int velocity)
        : GameObject(position),
          direction_x(position[DIRECTION_POS]), direction_y(FORWARD),
          velocity(velocity), current_vel_x(0), current_vel_y(0) {}

Movable::Movable(const int x, const int y,
                 const int direction_x, const int velocity)
        : GameObject(x, y), direction_x(direction_x), direction_y(FORWARD),
          velocity(velocity), current_vel_x(0), current_vel_y(0) {}

void Movable::reset_position() {
    this->position.reset();
    this->direction_x = FORWARD;
    this->direction_y = FORWARD;
}

void Movable::change_x_movement(bool start, bool forward) {
    if (start)
        this->current_vel_x = this->velocity;
    else
        this->current_vel_x = 0;
    if (forward)
        this->direction_x = FORWARD;
    else
        this->direction_x = BACKWARD;
}

void Movable::change_y_movement(bool start, bool forward) {
    if (start)
        this->current_vel_y = this->velocity;
    else
        this->current_vel_y = 0;
    if (forward)
        this->direction_y = FORWARD;
    else
        this->direction_y = BACKWARD;
}

void Movable::move() {
    this->position.move(this->direction_x * this->current_vel_x,
                        this->direction_y * this->current_vel_y);
}

std::vector<int> Movable::get_position() {
    std::vector<int> position = GameObject::get_position();
    position.push_back(this->direction_x);
    position.push_back(this->direction_y);
    return position;
}

Movable::~Movable() {}
