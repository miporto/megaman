#include <string>
#include <algorithm>
#include <vector>

#include "Cannon.h"
#include "MegaMan.h"
#include "Enemy.h"
#include "Factory.h"

Projectile::Projectile(const std::string& name,
                       int damage,
                       int velocity_x, int velocity_y,
                       const std::vector<int>& initial_position) :
        Movable(initial_position, velocity_x, velocity_y),
        name(name), damage(damage){}

bool Projectile::is_dead() {
    //TODO Devuelve true si toco a algun jugador o si se fue del mapa?
    return false;
}

std::string Projectile::info() {
    std::vector<int> pos = this->get_position();
    json info = { {"x", pos[X_COORD_POS]},
                  {"y", pos[Y_COORD_POS]},
                  {"direction x", pos[DIRECTION_X_POS]},
                  {"direction y", pos[DIRECTION_Y_POS]} };
    return info.dump();
}

const std::string& Projectile::get_name() { return this->name; }

void Projectile::collide_with(Enemy* enemy) {
    enemy->decrease_energy(this->damage);
}

void Projectile::collide_with(Object* object) {}

void Projectile::collide_with(Projectile* projectile) {}

void Projectile::collide_with(MegaMan* mm) {
    mm->decrease_energy(this->damage);
}

void Projectile::execute_collision_with(GameObject* other) {
    other->collide_with(this);
}

bool Projectile::is_enemy() { return false; }

Projectile::~Projectile() {}

Plasma::Plasma(int damage, int velocity_x, int velocity_y,
               const std::vector<int>& initial_position)
        : Projectile(PLASMA_NAME, damage, velocity_x,
                     velocity_y, initial_position) {}

void Plasma::tick() {
    //TODO
}

Bomb::Bomb(int damage, int velocity_x, int velocity_y,
           const std::vector<int>& initial_position)
        : Projectile(BOMB_NAME, damage, velocity_x,
                     velocity_y, initial_position) {}

void Bomb::tick() {
    //TODO
}

Magnet::Magnet(int damage, int velocity_x, int velocity_y,
               const std::vector<int>& initial_position)
        : Projectile(MAGNET_NAME, damage, velocity_x,
                     velocity_y, initial_position) {}

void Magnet::tick() {
    //TODO
}

Spark::Spark(int damage, int velocity_x, int velocity_y,
             const std::vector<int>& initial_position)
        : Projectile(SPARK_NAME, damage, velocity_x,
                     velocity_y, initial_position) {}

void Spark::tick() {
    //TODO
}

Fire::Fire(int damage, int velocity_x, int velocity_y,
           const std::vector<int>& initial_position)
        : Projectile(FIRE_NAME, damage, velocity_x,
                     velocity_y, initial_position) {}

void Fire::tick() {
    //TODO
}

Ring::Ring(int damage, int velocity_x, int velocity_y,
           const std::vector<int>& initial_position)
        : Projectile(RING_NAME, damage, velocity_x,
                     velocity_y, initial_position) {}

void Ring::tick() {
    //TODO
}

Ammo::Ammo(const std::string& name, int max) :
        name(name), max(max), quantity(max) {}

Projectile* Ammo::use(const std::vector<int>& position) {
    if (this->quantity) {
        this->quantity--;
        return ProjectileFactory::projectile(this->name, position);
    }
    return NULL;
}

Ammo::~Ammo() {}

Cannon::Cannon() {
    this->ammos.push_back(AmmoFactory::ammo(PLASMA_NAME));
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
