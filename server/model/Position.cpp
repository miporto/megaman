#include <string>
#include <vector>
#include <math.h>

#include "Position.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1

Position::Position(const float x, const float y) : x(x), y(y) {}

Position::Position(const std::vector<float>& position)
        : x(position[X_COORD_POS]), y(position[Y_COORD_POS]) {}

void Position::move(float x_amount, float y_amount) {
    this->x += x_amount;
    this->y += y_amount;
    this->truncate_at_two();
}

bool Position::out_of_range() {
    return (this->x < 0 || this->y < 0);
}

void Position::reset() {
    this->x = 0;
    this->y = 0;
}

std::vector<float> Position::get_position() const {
    std::vector<float> pos;
    pos.push_back(this->x);
    pos.push_back(this->y);
    return pos;
}

void Position::truncate_at_two() {
    this->x = floor(this->x * 100) / 100;
    this->y = floor(this->y * 100) / 100;
}

bool Position::operator==(const Position& other) const {
    return (this->x == other.x && this->y == other.y);
}

std::string Position::str() const {
    std::string str;
    str.append((char*)&this->x);
    str.append((char*)&this->y);
    return str;
}

Position* Position::clone() const { return new Position(*this); }

Position::~Position() {}
