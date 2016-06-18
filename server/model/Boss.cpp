#include <vector>
#include <utility>
#include <string>

#include "server/Logger.h"
#include "Boss.h"
#include "Enemy.h"
#include "Object.h"
#include "common/communication/Packet.h"
#include "Cannon.h"
#include "Factory.h"

#define BOSS_SIDE 1

#define BOMBMAN_SHOOT_FREC 35
#define BOMBMAN_JUMP_FREC 150
#define BOMBMAN_SHUFFLE_FREC 35
#define RINGMAN_JUMP_FREC 150
#define RINGMAN_SHUFFLE_FREC 10
#define FIREMAN_JUMP_FREC 150
#define FIREMAN_SHUFFLE_FREC 30
#define MAGNETMAN_SHOOT_FREC 20
#define MAGNETMAN_JUMP_FREC 100
#define MAGNETMAN_SHUFFLE_FREC 50
#define MAGNETMAN_STOP_FREC 65

Boss::Boss(const std::string& name, const std::vector<float>& position,
     const float velocity_x, const float velocity_y, int energy)
        : GravityAffectedMovable(position, velocity_x, velocity_y, BOSS_SIDE),
          name(name), initial_energy(energy), energy(energy), ticks(0) {
    this->change_x_direction();
}

const std::string& Boss::get_name() { return this->name; }

void Boss::decrease_energy(int amount) {
    if (this->energy < amount)
        this->energy = 0;
    else
        this->energy -= amount;
    Logger::instance()->out << INFO << "Boss " << this->get_name()
    << " has been shot. Remaining energy: " << this->energy;
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
    std::stringstream senergy;
    senergy << this->get_energy_percentage();

    json info = { {"x", sx.str()},
                  {"y", sy.str()},
                  {"direction x", (int)pos[DIRECTION_X_POS]},
                  {"direction y", (int)pos[DIRECTION_Y_POS]},
                  {"energy", senergy.str()},
                  {"id", id} };
    return std::make_pair(this->get_name(), info.dump());
}

bool Boss::shoots_per_tick() { return true; }

bool Boss::is_boss() { return true; }

float Boss::get_energy_percentage() {
    return ((float)this->energy / (float)this->initial_energy) * 100;
}

FloatUpdate* Boss::update(const int id) {
    Logger::instance()->out << ERROR << "BOSS SENDING ENERGY PERCENTAGE: "
    << this->get_energy_percentage();

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
        : Boss(BOMBMAN_NAME, position, velocity_x, velocity_y, energy) {
    this->start_x_movement();
}

void BombMan::collide_with(Projectile* projectile) {
    if (!projectile->get_name().compare(BOMB_NAME)) return;
    this->decrease_energy(projectile->hit());
}

void BombMan::shoot(GameObjectHandler* handler) {
    if (this->no_y_movement() && this->ticks % BOMBMAN_SHOOT_FREC == 0)
        handler->add_game_object(ProjectileFactory::projectile
                                         (BOMB_NAME, this->get_position(),
                                          false));
}

void BombMan::tick() {
    if (this->ticks % BOMBMAN_JUMP_FREC == 0)
        this->start_jump();
    if (this->no_y_movement() && this->ticks % BOMBMAN_SHUFFLE_FREC == 0)
        this->change_x_direction();
    this->move();
    this->ticks++;
}

const std::string BombMan::reward_ammo_name() { return BOMB_NAME; }

BombMan::~BombMan() {}

MagnetMan::MagnetMan(const std::vector<float>& position,
          const float velocity_x, const float velocity_y, int energy)
        : Boss(MAGNETMAN_NAME, position, velocity_x, velocity_y, energy) {
    this->start_x_movement();
}

void MagnetMan::collide_with(Projectile* projectile) {
    if (!projectile->get_name().compare(MAGNET_NAME)) return;
    this->decrease_energy(projectile->hit());
}

void MagnetMan::shoot(GameObjectHandler* handler) {
    if (this->ticks % MAGNETMAN_SHOOT_FREC == 0)
        handler->add_game_object(ProjectileFactory::projectile
                         (MAGNET_NAME, this->get_position(),
                          handler->closest_megaman(this->get_position()), false));
}

void MagnetMan::tick() {
    if (this->no_y_movement() && this->ticks % MAGNETMAN_JUMP_FREC == 0)
        this->start_jump();
    if (this->ticks % MAGNETMAN_SHUFFLE_FREC == 0) {
        this->change_x_direction();
        this->start_x_movement();
    }
    if (this->ticks % MAGNETMAN_STOP_FREC == 0)
        this->stop_x_movement();

    this->move();
    this->ticks++;
}

const std::string MagnetMan::reward_ammo_name() { return MAGNET_NAME; }

MagnetMan::~MagnetMan() {}

SparkMan::SparkMan(const std::vector<float>& position,
         const float velocity_x, const float velocity_y, int energy)
        : Boss(SPARKMAN_NAME, position, velocity_x, velocity_y, energy) {
    this->start_x_movement();
    this->start_jump();
}

void SparkMan::collide_with(Projectile* projectile) {
    if (!projectile->get_name().compare(SPARK_NAME)) return;
    this->decrease_energy(projectile->hit());
}

void SparkMan::shoot(GameObjectHandler* handler) {
    if (this->no_y_movement())
        handler->add_game_object(ProjectileFactory::projectile
                                         (SPARK_NAME,
                                          this->get_position(),
                                          false));
}

void SparkMan::tick() {
    if (this->no_y_movement()) {
        this->change_x_direction();
        this->start_jump();
    }
    this->move();
    this->ticks++;
}

const std::string SparkMan::reward_ammo_name() { return SPARK_NAME; }

SparkMan::~SparkMan() {}

RingMan::RingMan(const std::vector<float>& position,
        const float velocity_x, const float velocity_y, int energy)
        : Boss(RINGMAN_NAME, position, velocity_x, velocity_y, energy) {
    this->start_x_movement();
}

void RingMan::collide_with(Projectile* projectile) {
    if (!projectile->get_name().compare(RING_NAME)) return;
    this->decrease_energy(projectile->hit());
}

void RingMan::shoot(GameObjectHandler* handler) {
    handler->add_game_object(ProjectileFactory::projectile(RING_NAME,
                                                           this->get_position(),
                                                           false));
}

void RingMan::tick() {
    if (this->ticks % RINGMAN_JUMP_FREC == 0)
        this->start_jump();
    if (this->ticks % RINGMAN_SHUFFLE_FREC == 0)
        this->change_x_direction();
    this->move();
    this->ticks++;
}

const std::string RingMan::reward_ammo_name() { return RING_NAME; }

RingMan::~RingMan() {}

FireMan::FireMan(const std::vector<float>& position,
        const float velocity_x, const float velocity_y, int energy)
        : Boss(FIREMAN_NAME, position, velocity_x, velocity_y, energy) {
    this->start_x_movement();
}

void FireMan::collide_with(Projectile* projectile) {
    if (!projectile->get_name().compare(FIRE_NAME)) return;
    this->decrease_energy(projectile->hit());
}

void FireMan::shoot(GameObjectHandler* handler) {
    handler->add_game_object(ProjectileFactory::projectile(FIRE_NAME,
                                                           this->get_position(),
                                                           false));
}

void FireMan::tick() {
    if (this->ticks % FIREMAN_SHUFFLE_FREC == 0)
        this->change_x_direction();
    else if (this->ticks % FIREMAN_JUMP_FREC == 0)
        this->start_jump();
    this->move();
    this->ticks++;
}

const std::string FireMan::reward_ammo_name() { return FIRE_NAME; }

FireMan::~FireMan() {}
