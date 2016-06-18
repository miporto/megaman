#include <utility>
#include <vector>
#include <string>
#include <server/Logger.h>

#include "common/communication/Packet.h"
#include "Enemy.h"
#include "Object.h"
#include "Factory.h"
#include "GameObjectHandler.h"

#define AVG_PELLET_VEL 15
#define MET_HELMET_FREC 175
#define BUMBY_SHUFFLE_FREC 30
#define BUMBY_SHOOT_FREC 10
#define SNIPER_SHIELD_FREC 50
#define JUMPINGSNIPER_JUMP_FREC 15

#define ENEMY_SIDE 0.75

Enemy::Enemy(const std::string& name,
             const std::vector<float>& position,
             const float velocity_x, const float velocity_y,
             int energy) :
        IAMovable(position, velocity_x, velocity_y, ENEMY_SIDE),
        name(name), energy(energy), ticks(0) {}

void Enemy::collide_with(Enemy* enemy) {
    this->correct_position(enemy->get_position(), enemy->get_side());
}

void Enemy::collide_with(Object* object) {
    this->correct_position(object->get_position(), object->get_side());
}

void Enemy::collide_with(Boss* boss) {
    this->correct_position(boss->get_position(), boss->get_side());
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
    Logger::instance()->out << INFO << "Enemy " << this->get_name()
    << " has been shot. Remaining energy: " << this->energy;
}

bool Enemy::is_dead() { return this->energy == 0; }

bool Enemy::shoots_per_tick() { return true; }

bool Enemy::is_enemy() { return true; }

std::pair<std::string, std::string> Enemy::info(const int id) {
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

FloatUpdate* Enemy::update(const int id) {
    std::vector<float> pos = this->get_position();
    return new EnemyFloatUpdate(this->name, id,
                                pos[X_COORD_POS], pos[Y_COORD_POS],
                                false);
}

Enemy::~Enemy() {}

Met::Met(const std::vector<float>& position) :
        Enemy(MET_NAME, position,
              EnemyFactory::velocity_x(MET_NAME),
              EnemyFactory::velocity_y(MET_NAME),
              EnemyFactory::energy(MET_NAME)),
        helmet_on(true) {}

void Met::collide_with(Projectile* projectile) {
    if (!projectile->get_name().compare(PELLET_NAME)) return;

    if (!projectile->get_name().compare(BOMB_NAME) ||
        !projectile->get_name().compare(SPARK_NAME))
        this->decrease_energy(projectile->hit());

    else if (!this->helmet_on)
        this->decrease_energy(projectile->hit());

    projectile->hit();
}

void Met::shoot(GameObjectHandler* handler) {
    if (!helmet_on) {
        handler->add_game_object(new Pellet(-2 * AVG_PELLET_VEL, 0, this->get_position()));
        handler->add_game_object(new Pellet(-1.66 * AVG_PELLET_VEL, AVG_PELLET_VEL, this->get_position()));
        handler->add_game_object(new Pellet(-AVG_PELLET_VEL, AVG_PELLET_VEL * 1.66, this->get_position()));
    }
}

void Met::tick() {
    if (this->ticks % MET_HELMET_FREC == 0)
        this->helmet_on = false;
    else
        this->helmet_on = true;

    this->ticks++;
}

FloatUpdate* Met::update(const int id) {
    std::vector<float> pos = this->get_position();
    return new EnemyFloatUpdate(MET_NAME, id,
                                pos[X_COORD_POS], pos[Y_COORD_POS],
                                this->helmet_on);
}

Met::~Met() {}

Bumby::Bumby(const std::vector<float>& position) :
        Enemy(BUMBY_NAME, position,
              EnemyFactory::velocity_x(BUMBY_NAME),
              EnemyFactory::velocity_y(BUMBY_NAME),
              EnemyFactory::energy(BUMBY_NAME)) {}

void Bumby::collide_with(Projectile* projectile) {
    if (!projectile->get_name().compare(PELLET_NAME)) return;

    this->decrease_energy(projectile->hit());
}

void Bumby::shoot(GameObjectHandler* handler) {
    if (this->ticks % BUMBY_SHOOT_FREC == 0)
        handler->add_game_object(new Pellet(0, -AVG_PELLET_VEL,
                                            this->get_position()));
}

void Bumby::tick() {
    if (this->ticks % BUMBY_SHUFFLE_FREC == 0) this->change_x_direction();
    this->move();

    this->ticks++;
}

Bumby::~Bumby() {}

Sniper::Sniper(const std::vector<float>& position) :
        Enemy(SNIPER_NAME, position,
              EnemyFactory::velocity_x(SNIPER_NAME),
              EnemyFactory::velocity_y(SNIPER_NAME),
              EnemyFactory::energy(SNIPER_NAME)),
        shield_on(true) {}

void Sniper::collide_with(Projectile* projectile) {
    if (!projectile->get_name().compare(PELLET_NAME)) return;

    if (!projectile->get_name().compare(FIRE_NAME) ||
            !projectile->get_name().compare(RING_NAME))
        this->decrease_energy(projectile->hit());

    else if (!this->shield_on)
        this->decrease_energy(projectile->hit());

    projectile->hit();
}

void Sniper::shoot(GameObjectHandler* handler) {
    if (!this->shield_on)
        handler->add_game_object(new Pellet(-AVG_PELLET_VEL, 0,
                                            this->get_position()));
}

void Sniper::tick() {
    if (this->ticks % SNIPER_SHIELD_FREC == 0)
        this->shield_on = false;
    else
        this->shield_on = true;

    this->ticks++;
}

FloatUpdate* Sniper::update(const int id) {
    std::vector<float> pos = this->get_position();
    return new EnemyFloatUpdate(SNIPER_NAME, id,
                                pos[X_COORD_POS], pos[Y_COORD_POS],
                                this->shield_on);
}

Sniper::~Sniper() {}

JumpingSniper::JumpingSniper(const std::vector<float>& position) :
        Enemy(JUMPING_SNIPER_NAME, position,
              EnemyFactory::velocity_x(JUMPING_SNIPER_NAME),
              EnemyFactory::velocity_y(JUMPING_SNIPER_NAME),
              EnemyFactory::energy(JUMPING_SNIPER_NAME)),
        shield_on(true) {}

void JumpingSniper::collide_with(Projectile* projectile) {
    if (!projectile->get_name().compare(PELLET_NAME)) return;

    if (!projectile->get_name().compare(FIRE_NAME) ||
        !projectile->get_name().compare(RING_NAME))
        this->decrease_energy(projectile->hit());

    else if (!this->shield_on)
        this->decrease_energy(projectile->hit());

    projectile->hit();
}

void JumpingSniper::shoot(GameObjectHandler* handler) {
    if (!this->shield_on) {
        handler->add_game_object(new Pellet(-AVG_PELLET_VEL, 0,
                                            this->get_position()));
        handler->add_game_object(new Pellet(AVG_PELLET_VEL, 0,
                                            this->get_position()));
    }
}

void JumpingSniper::tick() {
    if (this->ticks % SNIPER_SHIELD_FREC == 0)
        this->shield_on = false;
    else
        this->shield_on = true;

    if (this->ticks % JUMPINGSNIPER_JUMP_FREC == 0) this->change_y_direction();
    this->move();

    this->ticks++;
}

FloatUpdate* JumpingSniper::update(const int id) {
    std::vector<float> pos = this->get_position();
    return new EnemyFloatUpdate(JUMPING_SNIPER_NAME, id,
                                pos[X_COORD_POS], pos[Y_COORD_POS],
                                this->shield_on);
}

JumpingSniper::~JumpingSniper() {}
