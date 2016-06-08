#include <utility>
#include <string>
#include <algorithm>
#include <vector>

#include "Cannon.h"
#include "MegaMan.h"
#include "Enemy.h"
#include "Factory.h"

#define PELLET_DAMAGE 1
#define PROJECTILE_TIMEOUT 50

Projectile::Projectile(const std::string& name,
                       int damage,
                       float velocity_x, float velocity_y,
                       const std::vector<float>& initial_position) :
        Movable(initial_position, velocity_x, velocity_y),
        name(name), damage(damage), ticks(0), dead(false) {}

void Projectile::acknowledge_tick() {
    if (this->ticks > PROJECTILE_TIMEOUT)
        this->dead = true;
    this->ticks++;
}

bool Projectile::is_dead() {
    return this->dead;
}

std::pair<std::string, std::string> Projectile::info(const int id) {
    std::vector<float> pos = this->get_position();
    std::stringstream sx;
    sx << pos[X_COORD_POS];
    std::stringstream sy;
    sy << pos[Y_COORD_POS];

    json info = { {"x", sx.str()},
                  {"y", sy.str()},
                  {"id", id} };
    return std::make_pair(this->get_name(), info.dump());
}

const std::string& Projectile::get_name() { return this->name; }

int Projectile::hit() {
    this->dead = true;
    return this->damage;
}

void Projectile::collide_with(Enemy* enemy) {}

void Projectile::collide_with(Object* object) {}

void Projectile::collide_with(Projectile* projectile) {}

void Projectile::collide_with(MegaMan* mm) {
    mm->decrease_energy(this->hit());
}

void Projectile::execute_collision_with(GameObject* other) {
    other->collide_with(this);
}

bool Projectile::is_enemy() { return false; }

Projectile::~Projectile() {}

Plasma::Plasma(int damage, float velocity_x, float velocity_y,
               const std::vector<float>& initial_position)
        : Projectile(PLASMA_NAME, damage, velocity_x,
                     velocity_y, initial_position) {}

bool Plasma::tick() {
    this->acknowledge_tick();
    //TODO
    return this->it_moved();
}

Bomb::Bomb(int damage, float velocity_x, float velocity_y,
           const std::vector<float>& initial_position)
        : Projectile(BOMB_NAME, damage, velocity_x,
                     velocity_y, initial_position) {}

bool Bomb::tick() {
    this->acknowledge_tick();
    //TODO
    return this->it_moved();
}

Magnet::Magnet(int damage, float velocity_x, float velocity_y,
               const std::vector<float>& initial_position)
        : Projectile(MAGNET_NAME, damage, velocity_x,
                     velocity_y, initial_position) {}

bool Magnet::tick() {
    this->acknowledge_tick();
    //TODO
    return this->it_moved();
}

Spark::Spark(int damage, float velocity_x, float velocity_y,
             const std::vector<float>& initial_position)
        : Projectile(SPARK_NAME, damage, velocity_x,
                     velocity_y, initial_position) {}

bool Spark::tick() {
    this->acknowledge_tick();
    //TODO
    return this->it_moved();
}

Fire::Fire(int damage, float velocity_x, float velocity_y,
           const std::vector<float>& initial_position)
        : Projectile(FIRE_NAME, damage, velocity_x,
                     velocity_y, initial_position) {}

bool Fire::tick() {
    this->acknowledge_tick();
    //TODO
    return this->it_moved();
}

Ring::Ring(int damage, float velocity_x, float velocity_y,
           const std::vector<float>& initial_position)
        : Projectile(RING_NAME, damage, velocity_x,
                     velocity_y, initial_position) {}

bool Ring::tick() {
    this->acknowledge_tick();
    //TODO
    return this->it_moved();
}

Pellet::Pellet(float velocity_x, float velocity_y,
           const std::vector<float>& initial_position)
        : Projectile(PELLET_NAME, PELLET_DAMAGE, velocity_x,
                     velocity_y, initial_position) {}

bool Pellet::tick() {
    this->acknowledge_tick();
    this->move();
    return this->it_moved();
}

Ammo::Ammo(const std::string& name, int max) :
        name(name), max(max), quantity(max) {}

Projectile* Ammo::use(const std::vector<float>& position) {
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

Projectile* Cannon::shoot(const std::vector<float>& position) {
    return this->current_ammo->use(position);
}

Cannon::~Cannon() {
    for (unsigned int i = 0; i < this->ammos.size(); ++i)
        delete this->ammos[i];
}
