#include <string>

#include "server/Factory.h"
#include "Player.h"

Player::Player(const std::string& name) :
        name(name), megaman(MegaManFactory::velocity()) {}

Player::~Player() {}
