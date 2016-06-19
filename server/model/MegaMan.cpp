#include <utility>
#include <string>
#include <vector>

#include "server/Logger.h"
#include "MegaMan.h"
#include "Enemy.h"
#include "Factory.h"
#include "common/communication/Packet.h"
#include "GameObjectHandler.h"

#define MEGAMAN_SIDE 0.75

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
    return this->current_energy <= 0 && this->lives <= 0;
}

void EnergyTank::reset() {
    if (!this->lives) {
        this->current_energy = 0;
        return;
    }
    this->lives--;
    this->current_energy = this->max_energy;
}

int EnergyTank::get_energy() {
    return this->current_energy;
}

float EnergyTank::get_energy_percentage() {
    return ((float)this->current_energy / (float)this->max_energy) * 100;
}

EnergyTank::~EnergyTank() {}

MegaMan::MegaMan(const std::string& name) :
        UserMovable(MegaManFactory::respawn_point(),
                    MegaManFactory::velocity_x(),
                    MegaManFactory::velocity_y(),
                    MEGAMAN_SIDE),
        name(name) {}

const std::string& MegaMan::get_name() {
    return this->name;
}

void MegaMan::decrease_energy(int amount) {
    this->tank.decrease_energy(amount);
    Logger::instance()->out << INFO << "Player " << this->get_name()
    << " has been shot. Remaining energy: " << this->tank.get_energy();
}

void MegaMan::kill() {
    this->tank.reset();
    this->reset_position();
}

bool MegaMan::is_dead() {
    return this->tank.is_empty();
}

void MegaMan::shoot(GameObjectHandler* handler) {
    std::vector<float> projectile_initial_pos = this->get_position();
    this->get_initial_position_for_shot(projectile_initial_pos,
                                        this->get_side());

    this->cannon.shoot(handler, projectile_initial_pos);
}

void MegaMan::tick() {
    try {
        this->move();
    } catch (const MovableError& e) {
        this->kill();
    }
}

std::pair<std::string, std::string> MegaMan::info(const int id) {
    std::vector<float> pos = this->get_position();
    std::stringstream sx;
    sx << pos[X_COORD_POS];
    std::stringstream sy;
    sy << pos[Y_COORD_POS];
    std::stringstream senergy;
    senergy << this->tank.get_energy_percentage();

    json info = { {"name", this->get_name()},
                  {"x", sx.str()},
                  {"y", sy.str()},
                  {"direction x", (int)pos[DIRECTION_X_POS]},
                  {"direction y", (int)pos[DIRECTION_Y_POS]},
                  {"energy", senergy.str()},
                  {"id", id} };

    return std::make_pair(MEGAMAN_NAME, info.dump());
}

FloatUpdate* MegaMan::update(const int id) {
    std::vector<float> pos = this->get_position();
    return new MegaManFloatUpdate(MEGAMAN_NAME, this->name, id,
                                  pos[X_COORD_POS], pos[Y_COORD_POS],
                                  (int)pos[DIRECTION_X_POS],
                                  (int)pos[DIRECTION_Y_POS],
                                  this->tank.get_energy_percentage());
}

bool MegaMan::is_megaman() { return true; }

void MegaMan::collide_with(Enemy* enemy) {
    this->correct_position(enemy->get_position(), enemy->get_side());
}

void MegaMan::collide_with(Object* object) {}

void MegaMan::collide_with(Projectile* projectile) {
    if (!projectile->get_name().compare(PLASMA_NAME)
        || projectile->was_thrown_by_megaman()) return;
    this->decrease_energy(projectile->hit());
}

void MegaMan::collide_with(Boss* boss) {
    this->correct_position(boss->get_position(), boss->get_side());
}

void MegaMan::collide_with(MegaMan* mm) {}

void MegaMan::execute_collision_with(GameObject* other) {
    other->collide_with(this);
}

void MegaMan::change_ammo(unsigned int ammo_id) {
    try {
        this->cannon.change_current_ammo(ammo_id);
        Logger::instance()->out << INFO << "Player " << this->get_name()
        << " changed cannon ammo to id: " << ammo_id;
    } catch (const CannonError& e) {
        Logger::instance()->out << INFO << "Player " << this->get_name()
        << " - Cannon: " << e.what() << " (id " << ammo_id << ")";
    }
}

void MegaMan::receive_new_ammo(std::string& name) {
    this->cannon.receive_new_ammo(name);
}

MegaMan::~MegaMan() {}
