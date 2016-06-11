#include <vector>
#include <iostream>
#include <cmath>

#include "Movable.h"

#define PX_PER_CELL_RATIO 50
#define FORWARD 1
#define BACKWARD -1
#define GRAVITY -0.01

Movable::Movable(const std::vector<float>& position,
                 const float velocity_x, const float velocity_y)
        : GameObject(position),
          velocity_x(velocity_x),
          velocity_y(velocity_y) {
    this->previous_position = this->get_position();
}

Movable::Movable(const float x, const float y,
                 const float velocity_x, const float velocity_y)
        : GameObject(x, y),
          velocity_x(velocity_x / PX_PER_CELL_RATIO),
          velocity_y(velocity_y / PX_PER_CELL_RATIO) {
    this->previous_position = this->get_position();
}

bool Movable::it_moved() {
    std::vector<float> current_position = this->get_position();
    return (current_position[X_COORD_POS] != previous_position[X_COORD_POS])
           || (current_position[Y_COORD_POS] != previous_position[Y_COORD_POS]);
}

void Movable::move() {
    this->previous_position = this->get_position();
    this->position.move(this->velocity_x, this->velocity_y);
}

void Movable::correct_position(const std::vector<float>& obstacle_pos,
                               int obstacle_side) {
    std::vector<float> pos = this->get_position();
    int side = this->get_side();
    float delta_x, delta_y;
    delta_x = delta_y = 0;

    float mass_center_y = pos[Y_COORD_POS] + (side / 2.0);
    float obs_mass_center_y = obstacle_pos[Y_COORD_POS] + (obstacle_side / 2.0);

    float mass_center_x = pos[X_COORD_POS] + (side / 2.0);
    float obs_mass_center_x = obstacle_pos[X_COORD_POS] + (obstacle_side / 2.0);

    if (mass_center_y > obs_mass_center_y) {
        delta_y = obstacle_pos[Y_COORD_POS] + obstacle_side - pos[Y_COORD_POS];
    } else {
        if (mass_center_x < obs_mass_center_x)
            delta_x = (-1) * (pos[X_COORD_POS] + side
                              - obstacle_pos[X_COORD_POS]);
        else
            delta_x = obstacle_pos[X_COORD_POS] + obstacle_side
                      - pos[X_COORD_POS];
    }

    this->position.move(delta_x, delta_y);
}

Movable::~Movable() {}

UserMovable::UserMovable(const float velocity_x, const float velocity_y)
        : Movable(0, 1, velocity_x, velocity_y), gravity(GRAVITY),
          direction_x(FORWARD), direction_y(FORWARD),
          current_vel_x(0), current_vel_y(0), on_stairs(false) {}

void UserMovable::change_x_movement(bool start, bool forward) {
    std::cout << "X movement" << std::endl;
    if (forward) {
        std::cout << "forward" << std::endl;
        this->direction_x = FORWARD;
    } else {
        std::cout << "backward" << std::endl;
        this->direction_x = BACKWARD;
    }
    if (start) {
        std::cout << "start" << std::endl;
        this->current_vel_x = this->velocity_x * this->direction_x;
    } else {
        std::cout << "stop" << std::endl;
        this->current_vel_x = 0;
    }
}

void UserMovable::change_y_movement(bool start, bool forward) {
    if (current_vel_y) return; //Si ya esta moviendose en y, ignoro la accion
    std::cout << "Y movement" << std::endl;
    if (forward) {
        std::cout << "forward" << std::endl;
        this->direction_y = FORWARD;
    } else {
        std::cout << "backward" << std::endl;
        this->direction_y = BACKWARD;
    }
    if (start) {
        std::cout << "start" << std::endl;
        this->current_vel_y = this->velocity_y * this->direction_y;
    } else {
        std::cout << "stop" << std::endl;
        this->current_vel_y = 0;
    }
}

void UserMovable::standing_on_stairs() { this->on_stairs = true; }

void UserMovable::move() {
    this->previous_position = this->get_position();
    if (!this->current_vel_x && !this->current_vel_y) return;

    float x_amount, y_amount;

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

    //if (this->position.out_of_range()) this->reset_position();
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

void UserMovable::correct_position(const std::vector<float>& obstacle_pos,
                                   int obstacle_side) {
    std::vector<float> pos = this->get_position();
    int side = this->get_side();
    float delta_x, delta_y;
    delta_x = delta_y = 0;

    float mass_center_y = pos[Y_COORD_POS] + (side / 2.0);
    float obs_mass_center_y = obstacle_pos[Y_COORD_POS] + (obstacle_side / 2.0);

    float mass_center_x = pos[X_COORD_POS] + (side / 2.0);
    float obs_mass_center_x = obstacle_pos[X_COORD_POS] + (obstacle_side / 2.0);

    if (mass_center_y > obs_mass_center_y) {
        delta_y = obstacle_pos[Y_COORD_POS] + obstacle_side - pos[Y_COORD_POS];
        this->reset_movement();
    } else {
        if (mass_center_x < obs_mass_center_x)
            delta_x = (-1) * (pos[X_COORD_POS] + side
                              - obstacle_pos[X_COORD_POS]);
        else
            delta_x = obstacle_pos[X_COORD_POS] + obstacle_side
                      - pos[X_COORD_POS];
        this->current_vel_x = 0;
    }

    this->position.move(delta_x, delta_y);
}

std::vector<float> UserMovable::get_position() {
    std::vector<float> position = GameObject::get_position();
//    std::cout << "MM pos: " << position[X_COORD_POS] << " "
//    << position[Y_COORD_POS] << std::endl;
    position.push_back(this->direction_x);
    position.push_back(this->direction_y);
    return position;
}

UserMovable::~UserMovable() {}
