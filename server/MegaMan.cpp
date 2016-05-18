#include "MegaMan.h"

#define MAX_ENERGY 50
#define INITIAL_LIVES 3

EnergyTank::EnergyTank() : lives(INITIAL_LIVES),
                           max_energy(MAX_ENERGY),
                           current_energy(MAX_ENERGY) {}

void EnergyTank::increase_energy(int amount) {
    this->current_energy += amount;
}

void EnergyTank::decrease_energy(int amount) {
    if (current_energy < amount && )


    this->current_energy -= amount;
}

EnergyTank::~EnergyTank() {}

MegaMan::MegaMan() {}

MegaMan::~MegaMan() {}