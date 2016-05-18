#include "MegaMan.h"

#define AMMO_KINDS 6

// A reemplazar por .JSON
#define AMMO_MAX 330
#define AMMO_VEL 5 // Cada tipo de ammo tiene vel diferente
#define AMMO_DAMAGE 5 // Cada tipo de ammo tiene damage diferente
#define MAX_ENERGY 50
#define INITIAL_LIVES 3
//

Ammo::Ammo() : max(AMMO_MAX),
               damage(AMMO_DAMAGE),
               vel(AMMO_VEL),
               quantity(AMMO_MAX) {}

void Ammo::use() {

}

Ammo::~Ammo() {}

Cannon::Cannon() : ammos(AMMO_KINDS) {}

Cannon::~Cannon() {}

EnergyTank::EnergyTank() : lives(INITIAL_LIVES),
                           max_energy(MAX_ENERGY),
                           current_energy(MAX_ENERGY) {}

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

MegaMan::MegaMan() {}

MegaMan::~MegaMan() {}