#include <string>

#include "MegaMan.h"
#include "Factory.h"

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
    if (this->lives) this->lives--;
    this->current_energy = this->max_energy;
}

EnergyTank::~EnergyTank() {}

MegaMan::MegaMan() :
        position(0,0), velocity(MegaManFactory::velocity()) {}

void MegaMan::decrease_energy(int amount) {
    this->tank.decrease_energy(amount);
}

void MegaMan::kill() {
    this->tank.reset();
    this->position.reset();
}

bool MegaMan::is_dead() {
    return this->tank.is_empty();
}

Projectile* MegaMan::shoot() {
    return this->cannon.shoot(this->position);
}

void MegaMan::change_ammo(unsigned int ammo_id) {
    this->cannon.change_current_ammo(ammo_id);
}

void MegaMan::receive_new_ammo(std::string& name) {
    this->cannon.receive_new_ammo(name);
}

void MegaMan::move(int x_amount, int y_amount) {
    this->position.move(x_amount, y_amount);
}

Position& MegaMan::get_position() {
    return this->position;
}

MegaMan::~MegaMan() {}
