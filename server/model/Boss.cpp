#include <vector>
#include <utility>
#include <string>

#include "Boss.h"
#include "Enemy.h"
#include "Object.h"
#include "common/communication/Packet.h"
#include "Cannon.h"

#define BOSS_SIDE 1

Boss::Boss(const std::string& name, const std::vector<float>& position,
     const float velocity_x, const float velocity_y, int energy)
        : GravityAffectedMovable(position, velocity_x, velocity_y, BOSS_SIDE),
          name(name), initial_energy(energy), energy(energy) {
    this->change_x_direction();
}

const std::string& Boss::get_name() { return this->name; }

void Boss::decrease_energy(int amount) {
    if (this->energy < amount)
        this->energy = 0;
    else
        this->energy -= amount;
}

bool Boss::is_dead() { return this->energy <= 0; }

void Boss::collide_with(Enemy* enemy) {
    this->correct_position(enemy->get_position(), enemy->get_side());
}

void Boss::collide_with(Object* object) {
    this->correct_position(object->get_position(), object->get_side());
}

void Boss::collide_with(Boss* boss) {
    this->correct_position(boss->get_position(), boss->get_side());
}

void Boss::collide_with(MegaMan* mm) {}

void Boss::execute_collision_with(GameObject* other) {
    other->collide_with(this);
}

std::pair<std::string, std::string> Boss::info(const int id) {
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

bool Boss::shoots_per_tick() { return true; }

bool Boss::is_boss() { return true; }

float Boss::get_energy_percentage() {
    return this->energy / this->initial_energy;
}

FloatUpdate* Boss::update(const int id) {
    std::vector<float> pos = this->get_position();
    return new BossFloatUpdate(this->name, id,
                               pos[X_COORD_POS], pos[Y_COORD_POS],
                               (int)pos[DIRECTION_X_POS],
                               (int)pos[DIRECTION_Y_POS],
                               this->get_energy_percentage());
}

Boss::~Boss() {}

BombMan::BombMan(const std::vector<float>& position,
        const float velocity_x, const float velocity_y, int energy)
        : Boss(BOMBMAN_NAME, position, velocity_x, velocity_y, energy) {}

void BombMan::collide_with(Projectile* projectile) {
    //TODO
}

void BombMan::shoot(GameObjectHandler* handler) {
    //TODO
}

void BombMan::tick() {
    //TODO
}

const std::string BombMan::reward_ammo_name() { return BOMB_NAME; }

BombMan::~BombMan() {}

MagnetMan::MagnetMan(const std::vector<float>& position,
          const float velocity_x, const float velocity_y, int energy)
        : Boss(MAGNETMAN_NAME, position, velocity_x, velocity_y, energy) {}

void MagnetMan::collide_with(Projectile* projectile) {
    //TODO
}

void MagnetMan::shoot(GameObjectHandler* handler) {
    //TODO
}

void MagnetMan::tick() {
    //TODO
}

const std::string MagnetMan::reward_ammo_name() { return MAGNET_NAME; }

MagnetMan::~MagnetMan() {}

SparkMan::SparkMan(const std::vector<float>& position,
         const float velocity_x, const float velocity_y, int energy)
        : Boss(SPARKMAN_NAME, position, velocity_x, velocity_y, energy) {}

void SparkMan::collide_with(Projectile* projectile) {
    //TODO
}

void SparkMan::shoot(GameObjectHandler* handler) {
    //TODO
}

void SparkMan::tick() {
    //TODO
}

const std::string SparkMan::reward_ammo_name() { return SPARK_NAME; }

SparkMan::~SparkMan() {}

RingMan::RingMan(const std::vector<float>& position,
        const float velocity_x, const float velocity_y, int energy)
        : Boss(RINGMAN_NAME, position, velocity_x, velocity_y, energy) {}

void RingMan::collide_with(Projectile* projectile) {
    //TODO
}

void RingMan::shoot(GameObjectHandler* handler) {
    //TODO
}

void RingMan::tick() {
    //TODO
}

const std::string RingMan::reward_ammo_name() { return RING_NAME; }

RingMan::~RingMan() {}

FireMan::FireMan(const std::vector<float>& position,
        const float velocity_x, const float velocity_y, int energy)
        : Boss(FIREMAN_NAME, position, velocity_x, velocity_y, energy) {}

void FireMan::collide_with(Projectile* projectile) {
    //TODO
}

void FireMan::shoot(GameObjectHandler* handler) {
    //TODO
}

void FireMan::tick() {
    //TODO
}

const std::string FireMan::reward_ammo_name() { return FIRE_NAME; }

FireMan::~FireMan() {}
