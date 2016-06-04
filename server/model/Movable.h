#ifndef MOVABLE_H
#define MOVABLE_H

#include <vector>

#include "common/Position.h"
#include "GameObject.h"

class Movable : public GameObject {
    protected:
        int direction_x, direction_y;
        const int velocity_x, velocity_y;

    public:
        Movable(const std::vector<int>& position,
                const int velocity_x, const int velocity_y);
        Movable(const int x, const int y,
                const int direction_x,
                const int velocity_x, const int velocity_y);
        virtual void move();
        std::vector<int> get_position();
        virtual void correct_position(const std::vector<int>& obstacle_pos,
                                      int obstacle_side);
        virtual ~Movable();
};

class UserMovable : public Movable {
    private:
        const int gravity;
        int current_vel_x, current_vel_y;
        bool on_stairs;

    public:
        explicit UserMovable(const int velocity_x, const int velocity_y);
        void change_x_movement(bool pressed, bool forward);
        void change_y_movement(bool pressed, bool forward);
        void standing_on_stairs();
        void move();
        void reset_movement();
        void reset_position();
        void correct_position(const std::vector<int>& obstacle_pos,
                              int obstacle_side);
        ~UserMovable();
};

#endif //MOVABLE_H
