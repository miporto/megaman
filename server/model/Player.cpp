#include <string>

#include "server/Logger.h"
#include "Player.h"

Player::Player() : megaman(NULL) {}

void Player::set_name(const std::string& name) {
    Logger::instance()->out << INFO << "New player: " << name;
    this->name = name;
}

std::string& Player::get_name() { return this->name; }

MegaMan* Player::get_megaman() { return this->megaman; }

void Player::new_megaman() {
    delete this->megaman;
    this->megaman = new MegaMan(this->name);
}

bool Player::alive() { return !this->megaman->is_dead(); }

Player::~Player() { delete this->megaman; }
