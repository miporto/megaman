#include <utility>
#include <string>
#include <algorithm>
#include <vector>

#include "server/Logger.h"
#include "common/communication/Packet.h"
#include "Cannon.h"
#include "MegaMan.h"
#include "Object.h"
#include "Enemy.h"
#include "Factory.h"
#include "GameObjectHandler.h"

#define PROJECTILE_TIMEOUT 600
#define PROJECTILE_SIDE 0.2

#define PELLET_DAMAGE 1

#define BOMB_JUMP_FREC 20
#define FIRE_SHUFFLE_FREC 25
#define HORIZONTAL_SPARK_NUMBER 2
#define DOWNWARD_SPARK_NUMBER 3
#define HORIZONTAL_RING_NUMBER 2
#define DOWNWARD_RING_NUMBER 3

Projectile::Projectile(const std::string& name,
                       int damage,
                       float velocity_x, float velocity_y,
                       const std::vector<float>& initial_position,
                       bool thrown_by_megaman):
        ProjectileMovable(initial_position, velocity_x,
                          velocity_y, PROJECTILE_SIDE),
        name(name), damage(damage), dead(false),
        thrown_by_megaman(thrown_by_megaman), ticks(0) {}

void Projectile::acknowledge_tick() {
    if (this->ticks > PROJECTILE_TIMEOUT)
        this->dead = true;
    this->ticks++;
}

bool Projectile::is_dead() {
    return this->dead;
}

bool Projectile::was_thrown_by_megaman() {
    return this->thrown_by_megaman;
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

FloatUpdate* Projectile::update(const int id) {
    std::vector<float> pos = this->get_position();
    //Logger::instance()->out << INFO << "UPDATE Projectile pos: " <<
    //        pos[X_COORD_POS] << " " << pos[Y_COORD_POS];
    return new FloatUpdate(this->name, id, pos[X_COORD_POS], pos[Y_COORD_POS]);
}

const std::string& Projectile::get_name() { return this->name; }

int Projectile::hit() {
    this->dead = true;
    return this->damage;
}

void Projectile::collide_with(Enemy* enemy) {}

void Projectile::collide_with(Object* object) {
    if (!object->get_name().compare(STAIRS_NAME)) return;
    this->hit();
}

void Projectile::collide_with(Projectile* projectile) {}

void Projectile::collide_with(Boss* boss) {}

void Projectile::collide_with(MegaMan* mm) {}

void Projectile::execute_collision_with(GameObject* other) {
    other->collide_with(this);
}

Projectile::~Projectile() {}

Plasma::Plasma(int damage, float velocity_x, float velocity_y,
               const std::vector<float>& initial_position)
        : Projectile(PLASMA_NAME, damage, velocity_x,
                     velocity_y, initial_position, true) {
    this->disable_y_movement();
}

void Plasma::tick() {
    this->acknowledge_tick();
    this->move();
}

Bomb::Bomb(int damage, float velocity_x, float velocity_y,
           const std::vector<float>& initial_position, bool thrown_by_megaman)
        : Projectile(BOMB_NAME, damage, velocity_x,
                     velocity_y, initial_position, thrown_by_megaman),
          has_bounced(false) {}

void Bomb::collide_with(Object* object) {
    if (!object->get_name().compare(STAIRS_NAME)) return;
    if (!has_bounced) {
        this->bounce(object->get_position(), object->get_side());
        this->has_bounced = true;
    } else {
        Projectile::collide_with(object);
    }
}

void Bomb::tick() {
    this->acknowledge_tick();
    if (this->ticks % BOMB_JUMP_FREC == 0) this->change_y_direction();
    this->move();
}

Magnet::Magnet(int damage, float velocity_x, float velocity_y,
               const std::vector<float>& initial_position,
               const std::vector<float>& target_position,
               bool thrown_by_megaman)
        : Projectile(MAGNET_NAME, damage, velocity_x,
                     velocity_y, initial_position, thrown_by_megaman),
          target_position(target_position) {
    this->disable_y_movement();
}

void Magnet::tick() {
    this->acknowledge_tick();
    if (this->target_x_reached(target_position)) {
        this->enable_y_movement();
        if (this->target_below_proyectile(target_position))
            this->change_y_direction();
    }
    this->move();
}

int Spark::spark_number = 0;

Spark::Spark(int damage, float velocity_x, float velocity_y,
             const std::vector<float>& initial_position, bool thrown_by_megaman)
        : Projectile(SPARK_NAME, damage, velocity_x,
                     velocity_y, initial_position, thrown_by_megaman) {
    if (this->spark_number == HORIZONTAL_SPARK_NUMBER) {
        this->disable_y_movement();
    } else if (this->spark_number == DOWNWARD_SPARK_NUMBER) {
        this->change_y_direction();
        this->spark_number = 0;
    }

    this->spark_number++;
}

void Spark::tick() {
    this->acknowledge_tick();
    this->move();
}

Fire::Fire(int damage, float velocity_x, float velocity_y,
           const std::vector<float>& initial_position, bool thrown_by_megaman)
        : Projectile(FIRE_NAME, damage, velocity_x,
                     velocity_y, initial_position, thrown_by_megaman) {
    this->disable_y_movement();
}

void Fire::tick() {
    this->acknowledge_tick();
    if (this->ticks % FIRE_SHUFFLE_FREC == 0) this->change_x_direction();
    this->move();
}

int Ring::ring_number = 0;

Ring::Ring(int damage, float velocity_x, float velocity_y,
           const std::vector<float>& initial_position, bool thrown_by_megaman)
        : Projectile(RING_NAME, damage, velocity_x,
                     velocity_y, initial_position, thrown_by_megaman) {
    if (this->ring_number == HORIZONTAL_RING_NUMBER) {
        this->disable_y_movement();
    } else if (this->ring_number == DOWNWARD_RING_NUMBER) {
        this->change_y_direction();
        this->ring_number = 0;
    }

    this->ring_number++;
}

void Ring::collide_with(Object* object) {
    if (!object->get_name().compare(STAIRS_NAME)) return;
    this->bounce(object->get_position(), object->get_side());
}

void Ring::collide_with(Projectile* projectile) {
    this->bounce(projectile->get_position(), projectile->get_side());
}

void Ring::tick() {
    this->acknowledge_tick();
    this->move();
}

Pellet::Pellet(float velocity_x, float velocity_y,
           const std::vector<float>& initial_position)
        : Projectile(PELLET_NAME, PELLET_DAMAGE, velocity_x,
                     velocity_y, initial_position, false) {}

void Pellet::tick() {
    this->acknowledge_tick();
    this->move();
}

Ammo::Ammo(const std::string& name, int max) :
        name(name), max(max), quantity(max) {}

void Ammo::use(GameObjectHandler* handler, const std::vector<float>& position) {
    if (this->quantity) {
        this->quantity--;
        handler->add_game_object
                (ProjectileFactory::projectile(this->name, position, true));
    }
}

Ammo::~Ammo() {}

MagnetAmmo::MagnetAmmo(const std::string& name, int max) : Ammo(name, max) {}

void MagnetAmmo::use(GameObjectHandler* handler,
                     const std::vector<float>& position) {
    if (this->quantity) {
        this->quantity--;
        handler->add_game_object
                (ProjectileFactory::projectile(this->name, position,
                                  handler->closest_enemy_for_megaman(position),
                                               true));
    }
}

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
    else
        throw CannonError("Ammo is unavaiable");
}

void Cannon::shoot(GameObjectHandler* handler,
                   const std::vector<float>& position) {
    this->current_ammo->use(handler, position);
}

Cannon::~Cannon() {
    for (unsigned int i = 0; i < this->ammos.size(); ++i)
        delete this->ammos[i];
}

CannonError::CannonError(const std::string error_msg) throw()
        : SystemError(error_msg) {}
