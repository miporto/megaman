#include <string>
#include <vector>

#include "Position.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1

Position::Position(const int x, const int y) : x(x), y(y) {}

Position::Position(const std::vector<int>& position)
        : x(position[X_COORD_POS]), y(position[Y_COORD_POS]) {}

void Position::move(int x_amount, int y_amount) {
    this->x += x_amount;
    this->y += y_amount;
}

void Position::reset() {
    this->x = 0;
    this->y = 0;
}

bool Position::operator==(const Position& other) const {
    return (this->x == other.x && this->y == other.y);
}

std::vector<int> Position::get_position() const {
    std::vector<int> pos;
    pos.push_back(this->x);
    pos.push_back(this->y);
    return pos;
}

std::string Position::str() const {
    std::string str;
    str.append((char*)&this->x);
    str.append((char*)&this->y);
    return str;
}

Position* Position::clone() const { return new Position(*this); }

Position::~Position() {}
