#ifndef BOSS_H
#define BOSS_H

#include <vector>
#include <utility>
#include <string>

#include "Movable.h"
#include "Shooter.h"

#define BOMBMAN_NAME "BombMan"
#define MAGNETMAN_NAME "MagnetMan"
#define SPARKMAN_NAME "SparkMan"
#define RINGMAN_NAME "RingMan"
#define FIREMAN_NAME "FireMan"

class BossChamber;

class Boss : public Movable, public Shooter {
    private:
        const std::string name;
        const int initial_energy;
        int energy;

        float get_energy_percentage();

    public:
        Boss(const std::string& name, const std::vector<float>& position,
             const float velocity_x, const float velocity_y, int energy);
        const std::string& get_name();
        void decrease_energy(int amount);
        bool is_dead();
        void collide_with(Enemy* enemy);
        void collide_with(Object* object);
        virtual void collide_with(Projectile* projectile) = 0;
        void collide_with(Boss* boss);
        void collide_with(MegaMan* mm);
        void execute_collision_with(GameObject* other);
        virtual void shoot(GameObjectHandler* handler) = 0;
        virtual void tick() = 0;
        std::pair<std::string, std::string> info(const int id);
        bool shoots_per_tick();
        bool is_boss();
        FloatUpdate* update(const int id);
        virtual const std::string reward_ammo_name() = 0;
        virtual ~Boss();
};

class BombMan : public Boss {
    public:
        BombMan(const std::vector<float>& position,
             const float velocity_x, const float velocity_y, int energy);
        void collide_with(Projectile* projectile);
        void shoot(GameObjectHandler* handler);
        void tick();
        const std::string reward_ammo_name();
        ~BombMan();
};

class MagnetMan : public Boss {
    public:
        MagnetMan(const std::vector<float>& position,
             const float velocity_x, const float velocity_y, int energy);
        void collide_with(Projectile* projectile);
        void shoot(GameObjectHandler* handler);
        void tick();
        const std::string reward_ammo_name();
        ~MagnetMan();
};

class SparkMan : public Boss {
    public:
        SparkMan(const std::vector<float>& position,
             const float velocity_x, const float velocity_y, int energy);
        void collide_with(Projectile* projectile);
        void shoot(GameObjectHandler* handler);
        void tick();
        const std::string reward_ammo_name();
        ~SparkMan();
};

class RingMan : public Boss {
    public:
        RingMan(const std::vector<float>& position,
             const float velocity_x, const float velocity_y, int energy);
        void collide_with(Projectile* projectile);
        void shoot(GameObjectHandler* handler);
        void tick();
        const std::string reward_ammo_name();
        ~RingMan();
};

class FireMan : public Boss {
    public:
        FireMan(const std::vector<float>& position,
             const float velocity_x, const float velocity_y, int energy);
        void collide_with(Projectile* projectile);
        void shoot(GameObjectHandler* handler);
        void tick();
        const std::string reward_ammo_name();
        ~FireMan();
};

#endif //BOSS_H
