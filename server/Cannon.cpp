#include <utility>
#include <string>
#include <algorithm>

#include "Cannon.h"
#include "Factory.h"

Projectile::Projectile(int damage,
                       int velocity,
                       Position& initial_position) :
        damage(damage), velocity(velocity), position(initial_position) {}

std::pair<int, int> Projectile::get_position() {
    return this->position.get_position();
}

Projectile::~Projectile() {}

Plasma::Plasma(int damage, int velocity, Position& initial_position) :
        Projectile(damage, velocity, initial_position) {}

void Plasma::move() {
    //TODO
}

Bomb::Bomb(int damage, int velocity, Position& initial_position) :
        Projectile(damage, velocity, initial_position) {}

void Bomb::move() {
    //TODO
}

Magnet::Magnet(int damage, int velocity, Position& initial_position) :
        Projectile(damage, velocity, initial_position) {}

void Magnet::move() {
    //TODO
}

Spark::Spark(int damage, int velocity, Position& initial_position) :
        Projectile(damage, velocity, initial_position) {}

void Spark::move() {
    //TODO
}

Fire::Fire(int damage, int velocity, Position& initial_position) :
        Projectile(damage, velocity, initial_position) {}

void Fire::move() {
    //TODO
}

Ring::Ring(int damage, int velocity, Position& initial_position) :
        Projectile(damage, velocity, initial_position) {}

void Ring::move() {
    //TODO
}

Ammo::Ammo(std::string& name, int max) : name(name), max(max), quantity(max) {}

// Devuelve NULL si el jugador intenta disparar y no hay mas municiones
Projectile* Ammo::use(Position& position) {
    if (this->quantity) {
        this->quantity--;
        ProjectileFactory factory;
        return factory(this->name, position);
    }
    return NULL;
}

Ammo::~Ammo() {}

Cannon::Cannon() {
    AmmoFactory factory;
    this->ammos.push_back(factory("Plasma"));
    this->current_ammo = this->ammos[0];
}

void Cannon::receive_new_ammo(std::string& name) {
    AmmoFactory factory;
    this->ammos.push_back(factory(name));
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
