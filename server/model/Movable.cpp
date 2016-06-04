#include <vector>
#include <iostream>
#include <cmath>

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

void Movable::correct_position(const std::vector<int>& obstacle_pos,
                               int obstacle_side) {
    std::vector<int> pos = this->get_position();
    int side = this->get_side();
    int delta_x, delta_y;
    delta_x = delta_y = 0;

    if (this->direction_x * this->velocity > 0)
            delta_x = (-1) * (pos[X_COORD_POS] + side
                              - obstacle_pos[X_COORD_POS]);
    else if (this->direction_x * this->velocity < 0)
            delta_x = obstacle_pos[X_COORD_POS] + obstacle_side
                      - pos[X_COORD_POS];

    if (this->direction_y * this->velocity > 0)
            delta_y = (-1) * (pos[Y_COORD_POS] + side
                              - obstacle_pos[Y_COORD_POS]);
    else if (this->direction_y * this->velocity < 0)
            delta_y = obstacle_pos[Y_COORD_POS] + obstacle_side
                      - pos[Y_COORD_POS];

    this->position.move(delta_x, delta_y);
}

Movable::~Movable() {}

UserMovable::UserMovable(const int velocity)
        : Movable(0, 0, FORWARD, velocity), gravity(GRAVITY),
          current_vel_x(0), current_vel_y(0), on_stairs(false) {}

void UserMovable::change_x_movement(bool start, bool forward) {
    if (forward)
        this->direction_x = FORWARD;
    else
        this->direction_x = BACKWARD;
    if (start)
        this->current_vel_x = this->velocity * this->direction_x;
    else
        this->current_vel_x = 0;
}

void UserMovable::change_y_movement(bool start, bool forward) {
    if (current_vel_y) return; //Si ya esta moviendose en y, ignoro la accion

    if (forward)
        this->direction_y = FORWARD;
    else
        this->direction_y = BACKWARD;

    if (start)
        this->current_vel_y = this->velocity * this->direction_y;
    else
        this->current_vel_y = 0;
}

void UserMovable::standing_on_stairs() { this->on_stairs = true; }

void UserMovable::move() {
    int x_amount, y_amount;

    //MRU en eje x
    x_amount = this->current_vel_x;

    if (on_stairs) {
        //MRU en eje y
        y_amount = this->current_vel_y;

    } else {
        //MRUV en eje y
        this->current_vel_y = this->current_vel_y + this->gravity;
        y_amount = this->current_vel_y;
    }
    this->position.move(x_amount, y_amount);
    this->on_stairs = false;

    if (this->position.out_of_range()) this->reset_position();
}

void UserMovable::reset_movement() {
    this->current_vel_x = 0;
    this->current_vel_y = 0;
}

void UserMovable::reset_position() {
    this->position.reset();
    this->direction_x = FORWARD;
    this->direction_y = FORWARD;
    this->reset_movement();
}

void UserMovable::correct_position(const std::vector<int>& obstacle_pos,
                                   int obstacle_side) {
    std::vector<int> pos = this->get_position();
    int side = this->get_side();
    int delta_x, delta_y;
    delta_x = delta_y = 0;
    if (std::abs(this->current_vel_x) > std::abs(this->current_vel_y)) {
        if (this->current_vel_x > 0)
            delta_x = (-1) * (pos[X_COORD_POS] + side
                              - obstacle_pos[X_COORD_POS]);
        if (this->current_vel_x < 0)
            delta_x = obstacle_pos[X_COORD_POS] + obstacle_side
                      - pos[X_COORD_POS];
    } else {
        if (this->current_vel_y > 0)
            delta_y = (-1) * (pos[Y_COORD_POS] + side
                              - obstacle_pos[Y_COORD_POS]);
        if (this->current_vel_y < 0) {
            delta_y = obstacle_pos[Y_COORD_POS] + obstacle_side
                      - pos[Y_COORD_POS];
            this->reset_movement();
        }
    }
    this->position.move(delta_x, delta_y);
}

UserMovable::~UserMovable() {}
