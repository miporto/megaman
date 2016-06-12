#ifndef BOSS_H
#define BOSS_H

#include <vector>
#include <utility>
#include <string>

#include "Movable.h"

#define BOMBMAN_NAME "BombMan"
#define MAGNETMAN_NAME "MagnetMan"
#define SPARKMAN_NAME "SparkMan"
#define RINGMAN_NAME "RingMan"
#define FIREMAN_NAME "FireMan"

class BossChamber;

class Boss : public Movable {
    private:
        const std::string name;
        int energy;
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
        virtual void shoot(BossChamber* chamber) = 0;
        virtual void tick() = 0;
        std::pair<std::string, std::string> info(const int id);
        FloatUpdate* update(const int id);
        virtual ~Boss();
};

class BombMan : public Boss {
    public:
        BombMan(const std::vector<float>& position,
             const float velocity_x, const float velocity_y, int energy);
        void collide_with(Projectile* projectile);
        void shoot(BossChamber* chamber);
        void tick();
        ~BombMan();
};

class MagnetMan : public Boss {
    public:
        MagnetMan(const std::vector<float>& position,
             const float velocity_x, const float velocity_y, int energy);
        void collide_with(Projectile* projectile);
        void shoot(BossChamber* chamber);
        void tick();
        ~MagnetMan();
};

class SparkMan : public Boss {
    public:
        SparkMan(const std::vector<float>& position,
             const float velocity_x, const float velocity_y, int energy);
        void collide_with(Projectile* projectile);
        void shoot(BossChamber* chamber);
        void tick();
        ~SparkMan();
};

class RingMan : public Boss {
    public:
        RingMan(const std::vector<float>& position,
             const float velocity_x, const float velocity_y, int energy);
        void collide_with(Projectile* projectile);
        void shoot(BossChamber* chamber);
        void tick();
        ~RingMan();
};

class FireMan : public Boss {
    public:
        FireMan(const std::vector<float>& position,
             const float velocity_x, const float velocity_y, int energy);
        void collide_with(Projectile* projectile);
        void shoot(BossChamber* chamber);
        void tick();
        ~FireMan();
};

#endif //BOSS_H
