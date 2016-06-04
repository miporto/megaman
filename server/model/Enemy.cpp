#include <vector>
#include <string>

#include "Enemy.h"
#include "Object.h"
#include "Factory.h"

Enemy::Enemy(const std::string& name,
             const std::vector<int>& position,
             const int velocity,
             int energy) :
        Movable(position, velocity),
        name(name),
        energy(energy) {}

void Enemy::collide_with(Enemy* enemy) {
    this->correct_position(enemy->get_position(), enemy->get_side());
}

void Enemy::collide_with(Object* object) {
    this->correct_position(object->get_position(), object->get_side());
}

void Enemy::collide_with(Projectile* projectile) {}

void Enemy::collide_with(MegaMan* mm) {}

void Enemy::execute_collision_with(GameObject* other) {
    other->collide_with(this);
}

const std::string& Enemy::get_name() { return this->name; }

void Enemy::decrease_energy(int amount) {
    if (this->energy < amount)
        this->energy = 0;
    else
        this->energy -= amount;
}

bool Enemy::is_dead() { return this->energy == 0; }

bool Enemy::is_enemy() { return true; }

std::string Enemy::info() {
    std::vector<int> pos = this->get_position();
    json info = { {"x", pos[X_COORD_POS]},
                  {"y", pos[Y_COORD_POS]},
                  {"direction x", pos[DIRECTION_X_POS]},
                  {"direction y", pos[DIRECTION_Y_POS]} };
    return info.dump();
}

Enemy::~Enemy() {}

Met::Met(const std::vector<int>& position) :
        Enemy(MET_NAME, position,
              EnemyFactory::velocity(MET_NAME),
              EnemyFactory::energy(MET_NAME)) {}

Projectile* Met::shoot() {
    //TODO
    return NULL;
}

void Met::tick() {
    //TODO
}

Met::~Met() {}

Bumby::Bumby(const std::vector<int>& position) :
        Enemy(BUMBY_NAME, position,
              EnemyFactory::velocity(BUMBY_NAME),
              EnemyFactory::energy(BUMBY_NAME)) {}

Projectile* Bumby::shoot() {
    //TODO
    return NULL;
}

void Bumby::tick() {
    //TODO
}

Bumby::~Bumby() {}

Sniper::Sniper(const std::vector<int>& position) :
        Enemy(SNIPER_NAME, position,
              EnemyFactory::velocity(SNIPER_NAME),
              EnemyFactory::energy(SNIPER_NAME)) {}

Projectile* Sniper::shoot() {
    //TODO
    return NULL;
}

void Sniper::tick() {
    //TODO
}

Sniper::~Sniper() {}

JumpingSniper::JumpingSniper(const std::vector<int>& position) :
        Enemy(JUMPING_SNIPER_NAME, position,
              EnemyFactory::velocity(JUMPING_SNIPER_NAME),
              EnemyFactory::energy(JUMPING_SNIPER_NAME)) {}

Projectile* JumpingSniper::shoot() {
    //TODO
    return NULL;
}

void JumpingSniper::tick() {
    //TODO
}

JumpingSniper::~JumpingSniper() {}
