#include <string>

#include "Factory.h"
#include "Player.h"

Player::Player(const std::string& name) :
        name(name) {}

bool Player::is_dead() {
    return this->megaman.is_dead();
}

Player::~Player() {}
