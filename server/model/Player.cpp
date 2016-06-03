#include <string>

#include "Player.h"

Player::Player() {}

void Player::set_name(const std::string& name) {
    std::cout << "Players name: " << name << std::endl;
    this->name = name;
}

std::string& Player::get_name() { return this->name; }

MegaMan* Player::get_megaman() { return this->megaman; }

void Player::new_megaman() {
    if (this->megaman) delete this->megaman;
    this->megaman = new MegaMan(this->name);
}

Player::~Player() { delete this->megaman; }
