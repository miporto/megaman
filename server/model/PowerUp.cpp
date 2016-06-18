#include <utility>
#include <string>
#include <vector>

#include "common/communication/Packet.h"
#include "MegaMan.h"
#include "PowerUp.h"

#define POWERUP_SIDE 0.2

#define EXTRALIFE_NAME "ExtraLife"
#define EXTRAENERGY_NAME "ExtraEnergy"
#define EXTRAPLASMA_NAME "ExtraPlasma"

#define EXTRA_ENERGY 4
#define EXTRA_PLASMA 4

PowerUp::PowerUp(const std::string& name, const std::vector<float>& position)
        : GameObject(position, POWERUP_SIDE), name(name), dead(false) {}

const std::string& PowerUp::get_name() { return this->name; }

void PowerUp::collide_with(Enemy* enemy) {}

void PowerUp::collide_with(Object* object) {}

void PowerUp::collide_with(Projectile* projectile) {}

void PowerUp::collide_with(Boss* boss) {}

void PowerUp::collide_with(PowerUp* pu) {}

void PowerUp::execute_collision_with(GameObject* other) {
    other->collide_with(this);
}

void PowerUp::tick() {}

void PowerUp::use() { this->dead = true; }

std::pair<std::string, std::string> PowerUp::info(const int id) {
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

FloatUpdate* PowerUp::update(const int id) {
    std::vector<float> pos = this->get_position();
    return new FloatUpdate(this->name, id, pos[X_COORD_POS], pos[Y_COORD_POS]);
}

bool PowerUp::is_dead() { return this->dead; }

PowerUp::~PowerUp() {}

ExtraLife::ExtraLife(const std::vector<float>& position) :
        PowerUp(EXTRALIFE_NAME, position) {}

void ExtraLife::collide_with(MegaMan* mm) {
    mm->extra_life();
    this->use();
}

ExtraLife::~ExtraLife() {}

ExtraEnergy::ExtraEnergy(const std::vector<float>& position) :
        PowerUp(EXTRAENERGY_NAME, position) {}

void ExtraEnergy::collide_with(MegaMan* mm) {
    mm->increase_energy(EXTRA_ENERGY);
    this->use();
}

ExtraEnergy::~ExtraEnergy() {}

ExtraPlasma::ExtraPlasma(const std::vector<float>& position) :
        PowerUp(EXTRAPLASMA_NAME, position) {}

void ExtraPlasma::collide_with(MegaMan* mm) {
    mm->increase_ammo(EXTRA_PLASMA);
    this->use();
}

ExtraPlasma::~ExtraPlasma() {}
