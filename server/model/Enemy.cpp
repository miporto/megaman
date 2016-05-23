#include "Enemy.h"
#include "Factory.h"

Enemy::Enemy(int x, int y, int energy) :
        position(x, y), energy(energy) {}

void Enemy::decrease_energy(int amount) {
    if (this->energy < amount)
        this->energy = 0;
    else
        this->energy -= amount;
}

bool Enemy::is_dead() { return this->energy == 0; }

Enemy::~Enemy() {}

Met::Met(int x, int y) :
        Enemy(x, y, EnemyFactory::energy("Met")),
        velocity(EnemyFactory::velocity("Met")) {}

Projectile* Met::shoot() {
    //TODO
    return NULL;
}

void Met::tick() {
    //TODO
}

Met::~Met() {}

Bumby::Bumby(int x, int y) :
        Enemy(x, y, EnemyFactory::energy("Bumby")),
        velocity(EnemyFactory::velocity("Bumby")) {}

Projectile* Bumby::shoot() {
    //TODO
    return NULL;
}

void Bumby::tick() {
    //TODO
}

Bumby::~Bumby() {}

Sniper::Sniper(int x, int y) :
        Enemy(x, y, EnemyFactory::energy("Sniper")),
        velocity(EnemyFactory::velocity("Sniper")) {}

Projectile* Sniper::shoot() {
    //TODO
    return NULL;
}

void Sniper::tick() {
    //TODO
}

Sniper::~Sniper() {}

JumpingSniper::JumpingSniper(int x, int y) :
        Enemy(x, y, EnemyFactory::energy("JumpingSniper")),
        velocity(EnemyFactory::velocity("JumpingSniper")) {}

Projectile* JumpingSniper::shoot() {
    //TODO
    return NULL;
}

void JumpingSniper::tick() {
    //TODO
}

JumpingSniper::~JumpingSniper() {}
