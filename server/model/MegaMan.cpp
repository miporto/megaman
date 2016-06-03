#include <string>
#include <vector>

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

MegaMan::MegaMan(const std::string& name) :
        Movable(INITIAL_X,
                INITIAL_Y,
                INITIAL_DIRECTION,
                MegaManFactory::velocity()),
        name(name) {}

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

void MegaMan::tick() {
    this->move();
}

std::string MegaMan::info() {
    std::vector<int> pos = this->get_position();
    json info = { {"x", pos[X_COORD_POS]},
                  {"y", pos[Y_COORD_POS]},
                  {"direction x", pos[DIRECTION_X_POS]},
                  {"direction y", pos[DIRECTION_Y_POS]},
                  {"energy", this->get_energy()} };
    return info.dump();
}

bool MegaMan::is_enemy() { return false; }

void MegaMan::collide_with(Enemy* enemy) { this->correct_position(); }

void MegaMan::collide_with(Object* object) {}

void MegaMan::collide_with(Projectile* projectile) {}

void MegaMan::collide_with(MegaMan* mm) {}

void MegaMan::execute_collision_with(GameObject* other) {
    other->collide_with(this);
}

void MegaMan::change_ammo(unsigned int ammo_id) {
    this->cannon.change_current_ammo(ammo_id);
}

void MegaMan::receive_new_ammo(std::string& name) {
    this->cannon.receive_new_ammo(name);
}

MegaMan::~MegaMan() {}
