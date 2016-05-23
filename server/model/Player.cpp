#include <string>

#include "Factory.h"
#include "Player.h"

Player::Player(const std::string& name) :
        name(name) {}

Player::~Player() {}
