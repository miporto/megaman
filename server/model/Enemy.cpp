#include <utility>
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

std::pair<std::string, std::string> Enemy::info(const int id) {
    std::vector<float> pos = this->get_position();
    json info = { {"x", (int)pos[X_COORD_POS]},
                  {"y", (int)pos[Y_COORD_POS]},
                  {"id", id} };
    return std::make_pair(this->get_name(), info.dump());
}

Enemy::~Enemy() {}

Met::Met(const std::vector<float>& position) :
        Enemy(MET_NAME, position,
              EnemyFactory::velocity_x(MET_NAME),
              EnemyFactory::velocity_y(MET_NAME),
              EnemyFactory::energy(MET_NAME)),
        ticks(0),
        helmet_on(true) {}

void Met::collide_with(Projectile* projectile) {
    if (!projectile->get_name().compare(PELLET_NAME)) return;

    if (!projectile->get_name().compare(BOMB_NAME) ||
        !projectile->get_name().compare(SPARK_NAME))
        this->decrease_energy(projectile->hit());

    else if (!this->helmet_on)
        this->decrease_energy(projectile->hit());
}

void Met::shoot(Map* map) {
    if (!helmet_on) {
        map->add_game_object(new Pellet(-1, 0, this->get_position()));
        map->add_game_object(new Pellet(-1, 0.88, this->get_position()));
        map->add_game_object(new Pellet(-1, 1, this->get_position()));
    }
}

void Met::tick() {
    if (this->ticks % 15 == 0)
        this->helmet_on = false;
    else
        this->helmet_on = true;
    this->ticks++;
}

Met::~Met() {}

Bumby::Bumby(const std::vector<float>& position) :
        Enemy(BUMBY_NAME, position,
              EnemyFactory::velocity_x(BUMBY_NAME),
              EnemyFactory::velocity_y(BUMBY_NAME),
              EnemyFactory::energy(BUMBY_NAME)),
        ticks(0) {}

void Bumby::collide_with(Projectile* projectile) {
    if (!projectile->get_name().compare(PELLET_NAME)) return;

    this->decrease_energy(projectile->hit());
}

void Bumby::shoot(Map* map) {
    map->add_game_object(new Pellet(0, -1, this->get_position()));
}

void Bumby::tick() {
    //TODO Movimiento?
}

Bumby::~Bumby() {}

Sniper::Sniper(const std::vector<float>& position) :
        Enemy(SNIPER_NAME, position,
              EnemyFactory::velocity_x(SNIPER_NAME),
              EnemyFactory::velocity_y(SNIPER_NAME),
              EnemyFactory::energy(SNIPER_NAME)),
        ticks(0),
        shield_on(true) {}

void Sniper::collide_with(Projectile* projectile) {
    if (!projectile->get_name().compare(PELLET_NAME)) return;

    if (!projectile->get_name().compare(FIRE_NAME) ||
            !projectile->get_name().compare(RING_NAME))
        this->decrease_energy(projectile->hit());

    else if (!this->shield_on)
        this->decrease_energy(projectile->hit());
}

void Sniper::shoot(Map* map) {
    if (!this->shield_on)
        map->add_game_object(new Pellet(-1, 0, this->get_position()));
}

void Sniper::tick() {
    //TODO Movimiento?
    if (this->ticks % 30 == 0)
        this->shield_on = false;
    else
        this->shield_on = true;
    this->ticks++;
}

Sniper::~Sniper() {}

JumpingSniper::JumpingSniper(const std::vector<float>& position) :
        Enemy(JUMPING_SNIPER_NAME, position,
              EnemyFactory::velocity_x(JUMPING_SNIPER_NAME),
              EnemyFactory::velocity_y(JUMPING_SNIPER_NAME),
              EnemyFactory::energy(JUMPING_SNIPER_NAME)),
        ticks(0),
        shield_on(true) {}

void JumpingSniper::collide_with(Projectile* projectile) {
    if (!projectile->get_name().compare(PELLET_NAME)) return;

    if (!projectile->get_name().compare(FIRE_NAME) ||
        !projectile->get_name().compare(RING_NAME))
        this->decrease_energy(projectile->hit());

    else if (!this->shield_on)
        this->decrease_energy(projectile->hit());
}

void JumpingSniper::shoot(Map* map) {
    if (!this->shield_on) {
        map->add_game_object(new Pellet(-1, 0, this->get_position()));
        map->add_game_object(new Pellet(1, 0, this->get_position()));
    }
}

void JumpingSniper::tick() {
    //TODO Movimiento (Saltos)
    if (this->ticks % 30 == 0)
        this->shield_on = false;
    else
        this->shield_on = true;
    this->ticks++;
}

JumpingSniper::~JumpingSniper() {}
