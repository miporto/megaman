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
        virtual void change_x_direction();
        virtual void change_y_direction();
        virtual ~IAMovable();
};

class ProjectileMovable : public IAMovable {
    private:
        const float potential_velocity_y;
    public:
        ProjectileMovable(const std::vector<float>& position,
                          const float velocity_x, const float velocity_y,
                          const float side);
        void disable_y_movement();
        void enable_y_movement();
        bool target_x_reached(const std::vector<float>& target_position);
        bool target_below_proyectile(const std::vector<float>& target_position);
        void bounce(const std::vector<float>& object_pos, float object_side);
        ~ProjectileMovable();
};

class GravityAffectedMovable : public IAMovable {
    protected:
        const float gravity;
        int direction_x, direction_y;
        float current_vel_x, current_vel_y;

    public:
        GravityAffectedMovable(const std::vector<float>& position,
                               const float velocity_x, const float velocity_y,
                               const float side);
        void jump();
        void change_x_direction();
        void change_y_direction();
        virtual void move();
        void correct_position(const std::vector<float>& obstacle_pos,
                          float obstacle_side);
        std::vector<float> get_position();
        ~GravityAffectedMovable();
};

class UserMovable : public GravityAffectedMovable {
    private:
        const std::vector<float> respawn_position;
        bool on_stairs;

        void reset_movement();

    public:
        UserMovable(const std::vector<float>& respawn_position,
                    const float velocity_x, const float velocity_y,
                    const float side);
        void change_x_movement(bool pressed, bool forward);
        void change_y_movement(bool pressed, bool forward);
        void standing_on_stairs();
        void move();
        void reset_position();
        //void correct_position(const std::vector<float>& obstacle_pos,
        //                        float obstacle_side);
        //std::vector<float> get_position();
        ~UserMovable();
};

class MovableError : public SystemError {
public:
    explicit MovableError(const std::string error_msg) throw();
};

#endif //MOVABLE_H
