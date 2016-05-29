#include <string>
#include <vector>

#include "Position.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1
#define DIRECTION_POS 3

Position::Position(const int x, const int y, const int direction)
        : x(x), y(y), direction(direction) {}

Position::Position(const std::vector<int>& position)
        : x(position[X_COORD_POS]),
          y(position[Y_COORD_POS]),
          direction(position[DIRECTION_POS]) {}

void Position::move(int x_amount, int y_amount) {
    this->x += (this->direction) * x_amount;
    this->y += (this->direction) * y_amount;
}

void Position::change_direction() {
    this->direction *= (-1);
}

void Position::reset() {
    this->x = 0;
    this->y = 0;
    this->direction = 1;
}

bool Position::operator==(const Position& other) const {
    return (this->x == other.x && this->y == other.y);
}

std::vector<int> Position::get_position() const {
    std::vector<int> pos;
    pos.push_back(this->x);
    pos.push_back(this->y);
    pos.push_back(this->direction);
    return pos;
}

std::string Position::str() const {
    std::string str;
    str.append((char*)&this->x);
    str.append((char*)&this->y);
    str.append((char*)&this->direction);
    return str;
}

Position* Position::clone() const { return new Position(*this); }

Position::~Position() {}
