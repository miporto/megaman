#ifndef POSITION_H
#define POSITION_H

#include <string>

class Position {
    private:
        int x, y;

    public:
        Position(int x, int y);
        void move(int x_amount, int y_amount);
        void reset();
        bool operator==(const Position& other) const;
        std::string str();
        ~Position();
};

#endif //POSITION_H
