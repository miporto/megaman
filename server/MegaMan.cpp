#include "MegaMan.h"
#include "Factory.h"

EnergyTank::EnergyTank(int initial_lives, int max_energy) {
    EnergyTankFactory factory;
    this->lives = factory.initial_lives();
    this->max_energy = factory.maximum_energy();
    this->current_energy = factory.maximum_energy();
}

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
    this->lives--;
    this->current_energy = this->max_energy;
}

EnergyTank::~EnergyTank() {}

MegaMan::~MegaMan() {}
