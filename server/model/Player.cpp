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
    for (unsigned int i = 0; i < this->ammo_rewards.size(); ++i)
        this->megaman->receive_new_ammo(this->ammo_rewards[i]);
}

bool Player::alive() { return !this->megaman->is_dead(); }

void Player::add_reward(const std::string& ammo_name) {
    Logger::instance()->out << INFO << "Player " << name <<
            " has been rewarded with ammo: " << ammo_name;
    this->ammo_rewards.push_back(ammo_name);
}

Player::~Player() { delete this->megaman; }
