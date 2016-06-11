#include <vector>
#include <utility>
#include <string>

#include "Boss.h"
#include "Enemy.h"
#include "Object.h"

Boss::Boss(const std::string& name, const std::vector<float>& position,
     const float velocity_x, const float velocity_y, int energy)
        : Movable(position, velocity_x, velocity_y),
          name(name), energy(energy) {}

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

std::pair<std::string, std::string> Boss::info() {
    std::vector<float> pos = this->get_position();
    json info = { {"x", (int)pos[X_COORD_POS]},
                  {"y", (int)pos[Y_COORD_POS]} };
    return std::make_pair(this->get_name(), info.dump());
}

Boss::~Boss() {}

BombMan::BombMan(const std::vector<float>& position,
        const float velocity_x, const float velocity_y, int energy)
        : Boss(BOMBMAN_NAME, position, velocity_x, velocity_y, energy) {}

void BombMan::collide_with(Projectile* projectile) {
    //TODO
}

void BombMan::shoot(BossChamber* chamber) {
    //TODO
}

void BombMan::tick() {
    //TODO
}

BombMan::~BombMan() {}

MagnetMan::MagnetMan(const std::vector<float>& position,
          const float velocity_x, const float velocity_y, int energy)
        : Boss(MAGNETMAN_NAME, position, velocity_x, velocity_y, energy) {}

void MagnetMan::collide_with(Projectile* projectile) {
    //TODO
}

void MagnetMan::shoot(BossChamber* chamber) {
    //TODO
}

void MagnetMan::tick() {
    //TODO
}

MagnetMan::~MagnetMan() {}

SparkMan::SparkMan(const std::vector<float>& position,
         const float velocity_x, const float velocity_y, int energy)
        : Boss(SPARKMAN_NAME, position, velocity_x, velocity_y, energy) {}

void SparkMan::collide_with(Projectile* projectile) {
    //TODO
}

void SparkMan::shoot(BossChamber* chamber) {
    //TODO
}

void SparkMan::tick() {
    //TODO
}

SparkMan::~SparkMan() {}

RingMan::RingMan(const std::vector<float>& position,
        const float velocity_x, const float velocity_y, int energy)
        : Boss(RINGMAN_NAME, position, velocity_x, velocity_y, energy) {}

void RingMan::collide_with(Projectile* projectile) {
    //TODO
}

void RingMan::shoot(BossChamber* chamber) {
    //TODO
}

void RingMan::tick() {
    //TODO
}

RingMan::~RingMan() {}

FireMan::FireMan(const std::vector<float>& position,
        const float velocity_x, const float velocity_y, int energy)
        : Boss(FIREMAN_NAME, position, velocity_x, velocity_y, energy) {}

void FireMan::collide_with(Projectile* projectile) {
    //TODO
}

void FireMan::shoot(BossChamber* chamber) {
    //TODO
}

void FireMan::tick() {
    //TODO
}

FireMan::~FireMan() {}
