#include <string>

#include "MegaMan.h"
#include "Factory.h"

#define INITIAL_X 0
#define INITIAL_Y 0
#define INITIAL_DIRECTION 1

EnergyTank::EnergyTank() :
        lives(EnergyTankFactory::initial_lives()),
        max_energy(EnergyTankFactory::maximum_energy()),
        current_energy(EnergyTankFactory::maximum_energy()) {}

void EnergyTank::increase_energy(int amount) {
    this->current_energy += amount;
}

void EnergyTank::decrease_energy(int amount) {
    if (this->current_energy < amount && this->lives > 0) {
        amount -= this->current_energy;
        this->reset();
        this->current_energy -= amount;
    } else if (this->current_energy < amount && this->lives == 0) {
        this->current_energy = 0;
    } else {
        this->current_energy -= amount;
    }
}

bool EnergyTank::is_empty() {
    return this->current_energy <= 0 && lives <= 0;
}

void EnergyTank::reset() {
    if (!this->lives) return;
    this->lives--;
    this->current_energy = this->max_energy;
}

int EnergyTank::get_energy() {
    return this->current_energy;
}

EnergyTank::~EnergyTank() {}

MegaMan::MegaMan() :
        Movable(INITIAL_X,
                INITIAL_Y,
                INITIAL_DIRECTION,
                MegaManFactory::velocity()) {}

void MegaMan::set_name(const std::string& name) {
    std::cout << "MM name: " << name << std::endl;
    this->name = name;
}

const std::string& MegaMan::get_name() {
    return this->name;
}

void MegaMan::decrease_energy(int amount) {
    this->tank.decrease_energy(amount);
}

int MegaMan::get_energy() {
    return this->tank.get_energy();
}

void MegaMan::kill() {
    this->tank.reset();
    this->reset_position();
}

bool MegaMan::is_dead() {
    return this->tank.is_empty();
}

Projectile* MegaMan::shoot() {
    return this->cannon.shoot(this->get_position());
}

void MegaMan::change_ammo(unsigned int ammo_id) {
    this->cannon.change_current_ammo(ammo_id);
}

void MegaMan::receive_new_ammo(std::string& name) {
    this->cannon.receive_new_ammo(name);
}

MegaMan::~MegaMan() {}
