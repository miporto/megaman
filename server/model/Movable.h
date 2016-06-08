#ifndef MOVABLE_H
#define MOVABLE_H

#include <vector>

#include "common/Position.h"
#include "GameObject.h"

class Movable : public GameObject {
    protected:
        const float velocity_x, velocity_y;
        std::vector<float> previous_position;

    public:
        Movable(const std::vector<float>& position,
                const float velocity_x, const float velocity_y);
        Movable(const float x, const float y,
                const float velocity_x, const float velocity_y);
        virtual void move();
        bool it_moved();
        virtual void correct_position(const std::vector<float>& obstacle_pos,
                                      int obstacle_side);
        virtual ~Movable();
};

class UserMovable : public Movable {
    private:
        const float gravity;
        int direction_x, direction_y;
        float current_vel_x, current_vel_y;
        bool on_stairs;

    public:
        explicit UserMovable(const float velocity_x, const float velocity_y);
        void change_x_movement(bool pressed, bool forward);
        void change_y_movement(bool pressed, bool forward);
        void standing_on_stairs();
        void move();
        void reset_movement();
        void reset_position();
        void correct_position(const std::vector<float>& obstacle_pos,
                              int obstacle_side);
        std::vector<float> get_position();
        ~UserMovable();
};

#endif //MOVABLE_H
