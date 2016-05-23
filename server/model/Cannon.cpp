#include <string>
#include <algorithm>

#include "Cannon.h"
#include "Factory.h"

Projectile::Projectile(int damage,
                       int velocity,
                       Position& initial_position) :
        damage(damage), velocity(velocity), position(initial_position) {}

Projectile::~Projectile() {}

Plasma::Plasma(int damage, int velocity, Position& initial_position) :
        Projectile(damage, velocity, initial_position) {}

void Plasma::tick() {
    //TODO
}

Bomb::Bomb(int damage, int velocity, Position& initial_position) :
        Projectile(damage, velocity, initial_position) {}

void Bomb::tick() {
    //TODO
}

Magnet::Magnet(int damage, int velocity, Position& initial_position) :
        Projectile(damage, velocity, initial_position) {}

void Magnet::tick() {
    //TODO
}

Spark::Spark(int damage, int velocity, Position& initial_position) :
        Projectile(damage, velocity, initial_position) {}

void Spark::tick() {
    //TODO
}

Fire::Fire(int damage, int velocity, Position& initial_position) :
        Projectile(damage, velocity, initial_position) {}

void Fire::tick() {
    //TODO
}

Ring::Ring(int damage, int velocity, Position& initial_position) :
        Projectile(damage, velocity, initial_position) {}

void Ring::tick() {
    //TODO
}

Ammo::Ammo(std::string& name, int max) : name(name), max(max), quantity(max) {}

// Devuelve NULL si el jugador intenta disparar y no hay mas municiones
Projectile* Ammo::use(Position& position) {
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

Projectile* Cannon::shoot(Position& position) {
    return this->current_ammo->use(position);
}

Cannon::~Cannon() {
    for (unsigned int i = 0; i < this->ammos.size(); ++i)
        delete this->ammos[i];
}
