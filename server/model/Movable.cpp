#include <vector>
#include <iostream>
#include <string>
#include <cmath>

#include "server/Logger.h"
#include "Movable.h"

#define PX_PER_CELL_RATIO 50
#define FORWARD 1
#define BACKWARD -1
#define GRAVITY -0.01

Movable::Movable(const std::vector<float>& position,
                 const float velocity_x, const float velocity_y,
                 const float side)
        : GameObject(position, side),
          velocity_x(velocity_x / PX_PER_CELL_RATIO),
          velocity_y(velocity_y / PX_PER_CELL_RATIO) {
    this->previous_position = this->get_position();
}

Movable::Movable(const std::vector<float>& position,
                 const int direction_x,
                 const float velocity_x, const float velocity_y,
                 const float side)
        : GameObject(position, side),
          velocity_x(direction_x * (velocity_x / PX_PER_CELL_RATIO)),
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
                               float obstacle_side) {
    std::vector<float> pos = this->get_position();
    float side = this->get_side();
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

std::vector<float> Movable::get_position() {
    std::vector<float> position = GameObject::get_position();
    int direction_x, direction_y;
    direction_x = (this->velocity_x >= 0) ? FORWARD : BACKWARD;
    direction_y = (this->velocity_y >= 0) ? FORWARD : BACKWARD;
    position.push_back(direction_x);
    position.push_back(direction_y);
    return position;
}

void Movable::get_initial_position_for_shot(std::vector<float>& shooter_pos,
                                            float shooter_side) {
    float initial_y = shooter_pos[Y_COORD_POS] + (shooter_side / 2.0);
    shooter_pos[Y_COORD_POS] = initial_y;
}

Movable::~Movable() {}

IAMovable::IAMovable(const std::vector<float>& position,
          const float velocity_x, const float velocity_y, const float side)
        : Movable(position, velocity_x, velocity_y, side) {}

IAMovable::IAMovable(const std::vector<float>& position,
          const int direction_x,
          const float velocity_x, const float velocity_y, const float side)
        : Movable(position, direction_x, velocity_x, velocity_y, side) {}

void IAMovable::change_x_direction() {
    this->velocity_x = (-1) * this->velocity_x;
}

void IAMovable::change_y_direction() {
    this->velocity_y = (-1) * this->velocity_y;
}

IAMovable::~IAMovable() {}

ProjectileMovable::ProjectileMovable(const std::vector<float>& position,
                                     const float velocity_x,
                                     const float velocity_y, const float side)
        : IAMovable(position, position[DIRECTION_X_POS],
                    velocity_x, velocity_y, side),
          potential_velocity_y(velocity_y) {}

void ProjectileMovable::enable_y_movement() {
    this->velocity_y = this->potential_velocity_y;
}

void ProjectileMovable::disable_y_movement() { this->velocity_y = 0; }

void ProjectileMovable::bounce(const std::vector<float>& object_pos,
                               float object_side) {
    std::vector<float> pos = this->get_position();
    float side = this->get_side();
    float mass_center_x = pos[X_COORD_POS] + (side / 2.0);
    float mass_center_y = pos[Y_COORD_POS] + (side / 2.0);

    float object_x = object_pos[X_COORD_POS];
    float object_y = object_pos[Y_COORD_POS];

    if (object_x < mass_center_x && mass_center_x < object_x + object_side) {
        // Choco de arriba o abajo
        this->change_y_direction();
    } else if (object_y < mass_center_y &&
            mass_center_y < object_y + object_side) {
        // Choco de izq o der
        this->change_x_direction();
    } else {
        // Choco juuuusto o muuuy cerca de la puntita
        this->change_y_direction();
        this->change_x_direction();
    }
}

bool ProjectileMovable::target_x_reached
        (const std::vector<float>& target_position) {
    std::vector<float> pos = this->get_position();
    if (pos[X_COORD_POS] <= target_position[X_COORD_POS] &&
            target_position[X_COORD_POS] <= pos[X_COORD_POS] + this->get_side())
        return true;
    return false;
}

bool ProjectileMovable::target_below_proyectile
        (const std::vector<float>& target_position) {
    std::vector<float> pos = this->get_position();
    if (target_position[Y_COORD_POS] < pos[Y_COORD_POS])
        return true;
    return false;
}

ProjectileMovable::~ProjectileMovable() {}

GravityAffectedMovable::GravityAffectedMovable
        (const std::vector<float>& position, const float velocity_x,
         const float velocity_y, const float side)
        : IAMovable(position, velocity_x, velocity_y, side),
          gravity(GRAVITY),
          direction_x(FORWARD), direction_y(FORWARD),
          current_vel_x(0), current_vel_y(0) {}

void GravityAffectedMovable::jump() {
    this->direction_y = FORWARD;
    this->current_vel_y = this->velocity_y * this->direction_y;
}

void GravityAffectedMovable::change_x_direction() {
    this->direction_x = (-1) * this->direction_x;
    this->current_vel_x = this->direction_x * this->current_vel_x;
}

void GravityAffectedMovable::change_y_direction() {
    this->direction_y = (-1) * this->direction_y;
    this->current_vel_y = this->direction_y * this->current_vel_y;
}

void GravityAffectedMovable::move() {
    this->previous_position = this->get_position();
    if (!this->current_vel_x && !this->current_vel_y) return;

    float x_amount, y_amount;

    //MRU en eje x
    x_amount = this->current_vel_x;

    //MRUV en eje y
    this->current_vel_y = this->current_vel_y + this->gravity;
    y_amount = this->current_vel_y;

    this->position.move(x_amount, y_amount);
}

void GravityAffectedMovable::correct_position
        (const std::vector<float>& obstacle_pos, float obstacle_side) {
    std::vector<float> pos = this->get_position();
    float side = this->get_side();
    float delta_x, delta_y;
    delta_x = delta_y = 0;

    float mass_center_y = pos[Y_COORD_POS] + (side / 2.0);
    float obs_mass_center_y = obstacle_pos[Y_COORD_POS] + (obstacle_side / 2.0);

    float mass_center_x = pos[X_COORD_POS] + (side / 2.0);
    float obs_mass_center_x = obstacle_pos[X_COORD_POS] + (obstacle_side / 2.0);

    if (mass_center_y > obs_mass_center_y) {
        delta_y = obstacle_pos[Y_COORD_POS] + obstacle_side - pos[Y_COORD_POS];
        this->current_vel_y = 0;
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

std::vector<float> GravityAffectedMovable::get_position() {
    std::vector<float> position = GameObject::get_position();
    position.push_back(this->direction_x);
    position.push_back(this->direction_y);
    return position;
}

GravityAffectedMovable::~GravityAffectedMovable() {}

UserMovable::UserMovable(const std::vector<float>& respawn_position,
                         const float velocity_x, const float velocity_y,
                         const float side)
        : GravityAffectedMovable(respawn_position, velocity_x,
                                 velocity_y, side),
          respawn_position(respawn_position), on_stairs(false) {}

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

void UserMovable::standing_on_stairs() {
    this->on_stairs = true;
    this->current_vel_y = 0;
    //TODO probar con if (current_vel_y != velocity_y) current_vel_y = 0;
}

void UserMovable::move() {
//    std::cout << get_position()[0] << ", " << get_position()[1] << "// ";
//    std::cout << current_vel_x << ", " << current_vel_y << std::endl;
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

    if (this->position.out_of_range())
        throw MovableError("Mega Man position out of range");
}

void UserMovable::reset_movement() {
    this->current_vel_x = 0;
    this->current_vel_y = 0;
}

void UserMovable::reset_position() {
    this->position.reset(respawn_position);
    this->direction_x = FORWARD;
    this->direction_y = FORWARD;
    this->reset_movement();
}

/*
void UserMovable::correct_position(const std::vector<float>& obstacle_pos,
                                   float obstacle_side) {
    std::vector<float> pos = this->get_position();
    float side = this->get_side();
    float delta_x, delta_y;
    delta_x = delta_y = 0;

    float mass_center_y = pos[Y_COORD_POS] + (side / 2.0);
    float obs_mass_center_y = obstacle_pos[Y_COORD_POS] + (obstacle_side / 2.0);

    float mass_center_x = pos[X_COORD_POS] + (side / 2.0);
    float obs_mass_center_x = obstacle_pos[X_COORD_POS] + (obstacle_side / 2.0);

    if (mass_center_y > obs_mass_center_y) {
        delta_y = obstacle_pos[Y_COORD_POS] + obstacle_side - pos[Y_COORD_POS];
        this->current_vel_y = 0;
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
    position.push_back(this->direction_x);
    position.push_back(this->direction_y);
    return position;
}
*/

UserMovable::~UserMovable() {}

MovableError::MovableError(const std::string error_msg) throw()
        : SystemError(error_msg) {}
