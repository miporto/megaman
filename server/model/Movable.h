#ifndef MOVABLE_H
#define MOVABLE_H

#include <vector>

#include "common/Position.h"
#include "GameObject.h"

class Movable : public GameObject {
    private:
        const int velocity;
    public:
        Movable(const std::vector<int>& position, const int velocity);
        Movable(const int x, const int y,
                const int direction, const int velocity);
        void reset_position();
        void move(int amount_x, int amount_y);
        void change_direction();
        virtual ~Movable();
};

#endif //MOVABLE_H
