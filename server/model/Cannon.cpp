#include <string>
#include <algorithm>
#include <vector>

#include "Cannon.h"
#include "Factory.h"

Projectile::Projectile(const std::string& name,
                       int damage,
                       int velocity,
                       const std::vector<int>& initial_position) :
        Movable(initial_position, velocity), name(name), damage(damage){}

const std::string& Projectile::get_name() { return this->name; }

Projectile::~Projectile() {}

Plasma::Plasma(int damage, int velocity,
               const std::vector<int>& initial_position)
        : Projectile(PLASMA_NAME, damage, velocity, initial_position) {}

void Plasma::tick() {
    //TODO
}

Bomb::Bomb(int damage, int velocity,
           const std::vector<int>& initial_position)
        : Projectile(BOMB_NAME, damage, velocity, initial_position) {}

void Bomb::tick() {
    //TODO
}

Magnet::Magnet(int damage, int velocity,
               const std::vector<int>& initial_position)
        : Projectile(MAGNET_NAME, damage, velocity, initial_position) {}

void Magnet::tick() {
    //TODO
}

Spark::Spark(int damage, int velocity,
             const std::vector<int>& initial_position)
        : Projectile(SPARK_NAME, damage, velocity, initial_position) {}

void Spark::tick() {
    //TODO
}

Fire::Fire(int damage, int velocity,
           const std::vector<int>& initial_position)
        : Projectile(FIRE_NAME, damage, velocity, initial_position) {}

void Fire::tick() {
    //TODO
}

Ring::Ring(int damage, int velocity,
           const std::vector<int>& initial_position)
        : Projectile(RING_NAME, damage, velocity, initial_position) {}

void Ring::tick() {
    //TODO
}

Ammo::Ammo(const std::string& name, int max) :
        name(name), max(max), quantity(max) {}

// Devuelve NULL si el jugador intenta disparar y no hay mas municiones
Projectile* Ammo::use(const std::vector<int>& position) {
    if (this->quantity) {
        this->quantity--;
        return ProjectileFactory::projectile(this->name, position);
    }
    return NULL;
}

Ammo::~Ammo() {}

Cannon::Cannon() {
    this->ammos.push_back(AmmoFactory::ammo("Plasma"));
    this->current_ammo = this->ammos[0];
}

void Cannon::receive_new_ammo(std::string& name) {
    this->ammos.push_back(AmmoFactory::ammo(name));
}

void Cannon::change_current_ammo(unsigned int ammo_id) {
    if (ammo_id < this->ammos.size())
        this->current_ammo = this->ammos[ammo_id];
}

Projectile* Cannon::shoot(const std::vector<int>& position) {
    return this->current_ammo->use(position);
}

Cannon::~Cannon() {
    for (unsigned int i = 0; i < this->ammos.size(); ++i)
        delete this->ammos[i];
}
