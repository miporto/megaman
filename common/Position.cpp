#include <utility>

#include "Position.h"

Position::Position(int x, int y) : x(x), y(y) {}

void Position::move(int x_amount, int y_amount) {
    this->x += x_amount;
    this->y += y_amount;
}

std::pair<int, int> Position::get_position() {
    return std::make_pair(this->x, this->y);
}

void Position::reset() {
    this->x = 0;
    this->y = 0;
}

bool Position::operator==(const Position& other) const {
    return (this->x == other.x && this->y == other.y);
}

Position::~Position() {}
