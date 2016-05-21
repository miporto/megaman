#ifndef POSITION_H
#define POSITION_H

#include <utility>

class Position {
    private:
        int x, y;

    public:
        Position(int x, int y);
        void move(int x_amount, int y_amount);
        std::pair<int, int> get_position();
        void reset();
        bool operator==(const Position& other) const;
        ~Position();
};

#endif //POSITION_H
