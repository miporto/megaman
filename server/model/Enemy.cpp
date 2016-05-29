#include <vector>
#include <string>

#include "Enemy.h"
#include "Factory.h"

Enemy::Enemy(const std::string& name,
             const std::vector<int>& position,
             const int velocity,
             int energy) :
        Movable(position, velocity),
        name(name),
        energy(energy) {}

const std::string& Enemy::get_name() { return this->name; }

void Enemy::decrease_energy(int amount) {
    if (this->energy < amount)
        this->energy = 0;
    else
        this->energy -= amount;
}

bool Enemy::is_dead() { return this->energy == 0; }

Enemy::~Enemy() {}

Met::Met(const std::vector<int>& position) :
        Enemy(MET_NAME, position,
              EnemyFactory::velocity("Met"),
              EnemyFactory::energy("Met")) {}

Projectile* Met::shoot() {
    //TODO
    return NULL;
}

Projectile* Met::tick() {
    //TODO
    return NULL;
}

Met::~Met() {}

Bumby::Bumby(const std::vector<int>& position) :
        Enemy(BUMBY_NAME, position,
              EnemyFactory::velocity("Bumby"),
              EnemyFactory::energy("Bumby")) {}

Projectile* Bumby::shoot() {
    //TODO
    return NULL;
}

Projectile* Bumby::tick() {
    //TODO
    return NULL;
}

Bumby::~Bumby() {}

Sniper::Sniper(const std::vector<int>& position) :
        Enemy(SNIPER_NAME, position,
              EnemyFactory::velocity("Sniper"),
              EnemyFactory::energy("Sniper")) {}

Projectile* Sniper::shoot() {
    //TODO
    return NULL;
}

Projectile* Sniper::tick() {
    //TODO
    return NULL;
}

Sniper::~Sniper() {}

JumpingSniper::JumpingSniper(const std::vector<int>& position) :
        Enemy(JUMPING_SNIPER_NAME, position,
              EnemyFactory::velocity("JumpingSniper"),
              EnemyFactory::energy("JumpingSniper")) {}

Projectile* JumpingSniper::shoot() {
    //TODO
    return NULL;
}

Projectile* JumpingSniper::tick() {
    //TODO
    return NULL;
}

JumpingSniper::~JumpingSniper() {}
