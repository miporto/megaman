#include <string>

#include "Position.h"

Position::Position(int x, int y) : x(x), y(y) {}

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

std::string Position::str() {
    std::string str;
    str.append((char*)&this->x);
    str.append((char*)&this->y);
    return str;
}

Position::~Position() {}
