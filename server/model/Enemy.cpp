#include <vector>
#include <string>

#include "Enemy.h"
#include "Object.h"
#include "Factory.h"
#include "Map.h"

Enemy::Enemy(const std::string& name,
             const std::vector<float>& position,
             const float velocity_x, const float velocity_y,
             int energy) :
        Movable(position, velocity_x, velocity_y),
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
    std::vector<float> pos = this->get_position();
    json info = { {"x", pos[X_COORD_POS]},
                  {"y", pos[Y_COORD_POS]} };
    return info.dump();
}

Enemy::~Enemy() {}

Met::Met(const std::vector<float>& position) :
        Enemy(MET_NAME, position,
              EnemyFactory::velocity_x(MET_NAME),
              EnemyFactory::velocity_y(MET_NAME),
              EnemyFactory::energy(MET_NAME)) {}

void Met::shoot(Map* map) {
    map->add_game_object(new Pellet(-1, 0, this->get_position()));
    map->add_game_object(new Pellet(-1, 0.33, this->get_position()));
    map->add_game_object(new Pellet(-1, 0.66, this->get_position()));
}

void Met::tick() {
    //TODO
}

Met::~Met() {}

Bumby::Bumby(const std::vector<float>& position) :
        Enemy(BUMBY_NAME, position,
              EnemyFactory::velocity_x(BUMBY_NAME),
              EnemyFactory::velocity_y(BUMBY_NAME),
              EnemyFactory::energy(BUMBY_NAME)) {}

void Bumby::shoot(Map* map) {
    map->add_game_object(new Pellet(0, -1, this->get_position()));
}

void Bumby::tick() {
    //TODO
}

Bumby::~Bumby() {}

Sniper::Sniper(const std::vector<float>& position) :
        Enemy(SNIPER_NAME, position,
              EnemyFactory::velocity_x(SNIPER_NAME),
              EnemyFactory::velocity_y(SNIPER_NAME),
              EnemyFactory::energy(SNIPER_NAME)) {}

void Sniper::shoot(Map* map) {
    map->add_game_object(new Pellet(-1, 0, this->get_position()));
}

void Sniper::tick() {
    //TODO
}

Sniper::~Sniper() {}

JumpingSniper::JumpingSniper(const std::vector<float>& position) :
        Enemy(JUMPING_SNIPER_NAME, position,
              EnemyFactory::velocity_x(JUMPING_SNIPER_NAME),
              EnemyFactory::velocity_y(JUMPING_SNIPER_NAME),
              EnemyFactory::energy(JUMPING_SNIPER_NAME)) {}

void JumpingSniper::shoot(Map* map) {
    map->add_game_object(new Pellet(-1, 0, this->get_position()));
    map->add_game_object(new Pellet(1, 0, this->get_position()));
}

void JumpingSniper::tick() {
    //TODO
}

JumpingSniper::~JumpingSniper() {}
