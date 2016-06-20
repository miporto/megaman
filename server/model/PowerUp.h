#ifndef POWERUP_H
#define POWERUP_H

#include <utility>
#include <string>
#include <vector>

#include "GameObject.h"

class Enemy;
class Projectile;
class MegaMan;

class PowerUp : public GameObject {
    private:
        const std::string name;
        bool dead;
        bool was_updated;

    public:
        PowerUp(const std::string& name, const std::vector<float>& position);
        const std::string& get_name();
        void collide_with(Enemy* enemy);
        void collide_with(Object* object);
        void collide_with(Projectile* projectile);
        void collide_with(Boss* boss);
        virtual void collide_with(MegaMan* mm) = 0;
        void collide_with(PowerUp* pu);
        void execute_collision_with(GameObject* other);
        void tick();
        void use();
        bool is_dead();
        std::pair<std::string, std::string> info(const int id);
        FloatUpdate* update(const int id);
        bool is_powerup();
        bool updated();
        virtual ~PowerUp();
};

class ExtraLife : public PowerUp {
    public:
        explicit ExtraLife(const std::vector<float>& position);
        void collide_with(MegaMan* mm);
        ~ExtraLife();
};

class ExtraEnergy : public PowerUp {
    public:
        explicit ExtraEnergy(const std::vector<float>& position);
        void collide_with(MegaMan* mm);
        ~ExtraEnergy();
};

class ExtraPlasma : public PowerUp {
    public:
        explicit ExtraPlasma(const std::vector<float>& position);
        void collide_with(MegaMan* mm);
        ~ExtraPlasma();
};

#endif //POWERUP_H
