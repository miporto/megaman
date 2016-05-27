#include <string>
#include <iostream>

#include "Factory.h"
#include "Player.h"

void Player::set_name(const std::string& name) {
    std::cout << "Players name: " << name << std::endl;
    this->name = name;
}

const std::string& Player::get_name() {
    return this->name;
}

bool Player::is_dead() {
    return this->megaman.is_dead();
}

Player::~Player() {}
