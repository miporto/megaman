#include <utility>
#include <string>
#include <vector>

#include "server/Logger.h"
#include "MegaMan.h"
#include "Enemy.h"
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
    if (!this->lives) return;
    this->lives--;
    this->current_energy = this->max_energy;
}

int EnergyTank::get_energy() {
    return this->current_energy;
}

EnergyTank::~EnergyTank() {}

MegaMan::MegaMan(const std::string& name) :
        UserMovable(MegaManFactory::respawn_point(),
                    MegaManFactory::velocity_x(),
                    MegaManFactory::velocity_y()),
        name(name) {}

const std::string& MegaMan::get_name() {
    return this->name;
}

void MegaMan::decrease_energy(int amount) {
    this->tank.decrease_energy(amount);
    Logger::instance()->out << INFO << "Player " << this->get_name()
    << " has been shot. Remaining energy: " << this->tank.get_energy();
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
    try {
        this->move();
    } catch (const MovableError& e) {
        this->kill();
    }
}

std::pair<std::string, std::string> MegaMan::info() {
    std::vector<float> pos = this->get_position();
    json info = { {"name", this->get_name()},
                  {"x", (int)pos[X_COORD_POS]},
                  {"y", (int)pos[Y_COORD_POS]},
                  {"direction x", (int)pos[DIRECTION_X_POS]},
                  {"direction y", (int)pos[DIRECTION_Y_POS]},
                  {"energy", this->get_energy()} };

    return std::make_pair("MegaMan", info.dump());
}

bool MegaMan::is_enemy() { return false; }

void MegaMan::collide_with(Enemy* enemy) {
    this->correct_position(enemy->get_position(), enemy->get_side());
}

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
