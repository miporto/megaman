#include <vector>
#include <iostream>

#include "Movable.h"

#define DIRECTION_X_POS 2
#define DIRECTION_Y_POS 3
#define PX_PER_CELL_RATIO 50
#define FORWARD 1
#define BACKWARD -1
#define GRAVITY -1

Movable::Movable(const std::vector<int>& position, const int velocity)
        : GameObject(position),
          direction_x(position[DIRECTION_X_POS]),
          direction_y(position[DIRECTION_Y_POS]),
          velocity(velocity / PX_PER_CELL_RATIO) {}

Movable::Movable(const int x, const int y,
                 const int direction_x, const int velocity)
        : GameObject(x, y), direction_x(direction_x), direction_y(FORWARD),
          velocity(velocity) {}

void Movable::move() {
    this->position.move(this->direction_x * this->velocity,
                        this->direction_y * this->velocity);
}

std::vector<int> Movable::get_position() {
    std::vector<int> position = GameObject::get_position();
    position.push_back(this->direction_x);
    position.push_back(this->direction_y);
    return position;
}

void Movable::correct_position() {
    //TODO Volver a la ultima posicion valida
}

Movable::~Movable() {}

UserMovable::UserMovable(const int velocity)
        : Movable(0, 0, FORWARD, velocity), gravity(GRAVITY),
          current_vel_x(0), current_vel_y(0), on_stairs(false) {}

void UserMovable::change_x_movement(bool start, bool forward) {
    if (start)
        this->current_vel_x = this->velocity;
    else
        this->current_vel_x = 0;
    if (forward)
        this->direction_x = FORWARD;
    else
        this->direction_x = BACKWARD;
}

void UserMovable::change_y_movement(bool start, bool forward) {
    if (current_vel_y) return; //Si ya esta moviendose en y, ignoro la accion

    if (start)
        this->current_vel_y = this->velocity;
    else
        this->current_vel_y = 0;
    if (forward)
        this->direction_y = FORWARD;
    else
        this->direction_y = BACKWARD;
}

void UserMovable::standing_on_stairs() {
    this->on_stairs = true;
}

void UserMovable::move() {
    int x, y;
    x = this->direction_x * this->current_vel_x;

    if (on_stairs)
        y = this->direction_y * this->current_vel_y;
    else
        y = (this->direction_y * this->current_vel_y) + this->gravity;

    this->position.move(x, y);
    this->on_stairs = false;

    if (this->position.out_of_range()) this->reset_position();
}

void UserMovable::reset_position() {
    this->position.reset();
    this->direction_x = FORWARD;
    this->direction_y = FORWARD;
    this->current_vel_x = 0;
    this->current_vel_y = 0;
}

void UserMovable::correct_position() {
    //TODO Volver a la ultima posicion valida
}

UserMovable::~UserMovable() {}
