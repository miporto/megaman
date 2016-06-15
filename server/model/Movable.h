#ifndef MOVABLE_H
#define MOVABLE_H

#include <vector>
#include <string>

#include "common/SystemError.h"
#include "Position.h"
#include "GameObject.h"

class Movable : public GameObject {
    protected:
        float velocity_x, velocity_y;
        std::vector<float> previous_position;

    public:
        Movable(const std::vector<float>& position,
                const float velocity_x, const float velocity_y,
                const float side);
        Movable(const std::vector<float>& position,
                const int direction_x,
                const float velocity_x, const float velocity_y,
                const float side);
        virtual void move();
        bool it_moved();
        virtual void correct_position(const std::vector<float>& obstacle_pos,
                                      float obstacle_side);
        std::vector<float> get_position();
        //TODO Mover a clase abstracta Shooter
        void get_initial_position_for_shot(std::vector<float>& shooter_pos,
                                           float shooter_side);
        virtual ~Movable();
};

class IAMovable : public Movable {
    public:
        IAMovable(const std::vector<float>& position,
                  const float velocity_x, const float velocity_y,
                  const float side);
        IAMovable(const std::vector<float>& position,
                  const int direction_x,
                  const float velocity_x, const float velocity_y,
                  const float side);
        void change_x_direction();
        void change_y_direction();
        ~IAMovable();
};

class ProjectileMovable : public IAMovable {
    public:
        ProjectileMovable(const std::vector<float>& position,
                          const float velocity_x, const float velocity_y,
                          const float side);
        ~ProjectileMovable();
};

class UserMovable : public Movable {
    private:
        const std::vector<float> respawn_position;
        const float gravity;
        int direction_x, direction_y;
        float current_vel_x, current_vel_y;
        bool on_stairs;

    public:
        UserMovable(const std::vector<float>& respawn_position,
                    const float velocity_x, const float velocity_y,
                    const float side);
        void change_x_movement(bool pressed, bool forward);
        void change_y_movement(bool pressed, bool forward);
        void standing_on_stairs();
        void move();
        void reset_movement();
        void reset_position();
        void correct_position(const std::vector<float>& obstacle_pos,
                              float obstacle_side);
        std::vector<float> get_position();
        ~UserMovable();
};

class MovableError : public SystemError {
public:
    explicit MovableError(const std::string error_msg) throw();
};

#endif //MOVABLE_H
