#ifndef ENEMY_H
#define ENEMY_H

#include <utility>
#include <vector>
#include <string>

#include "Position.h"
#include "Movable.h"
#include "Shooter.h"

#define MET_NAME "Met"
#define BUMBY_NAME "Bumby"
#define SNIPER_NAME "Sniper"
#define JUMPING_SNIPER_NAME "JumpingSniper"

class GameObjectHandler;
class Object;
class Projectile;
class MegaMan;

class Enemy : public IAMovable, public Shooter {
    private:
        const std::string name;
        int energy;

    protected:
        int ticks;

    public:
        Enemy(const std::string& name, const std::vector<float>& position,
              const float velocity_x, const float velocity_y, int energy);
        const std::string& get_name();
        void decrease_energy(int amount);
        bool is_dead();
        void collide_with(Enemy* enemy);
        void collide_with(Object* object);
        virtual void collide_with(Projectile* projectile) = 0;
        void collide_with(Boss* boss);
        void collide_with(MegaMan* mm);
        void collide_with(PowerUp* pu);
        void execute_collision_with(GameObject* other);
        virtual void tick() = 0;
        bool shoots_per_tick();
        bool is_enemy();
        virtual void shoot(GameObjectHandler* handler) = 0;
        std::pair<std::string, std::string> info(const int id);
        virtual FloatUpdate* update(const int id);
        virtual ~Enemy();
};

class Met : public Enemy {
    private:
        bool helmet_on;
    public:
        explicit Met(const std::vector<float>& position);
        void collide_with(Projectile* projectile);
        void shoot(GameObjectHandler* handler);
        void tick();
        FloatUpdate* update(const int id);
        ~Met();
};

class Bumby : public Enemy {
    public:
        explicit Bumby(const std::vector<float>& position);
        void collide_with(Projectile* projectile);
        void shoot(GameObjectHandler* handler);
        void tick();
        ~Bumby();
};

class Sniper : public Enemy {
    private:
        bool shield_on;
    public:
        explicit Sniper(const std::vector<float>& position);
        void collide_with(Projectile* projectile);
        void shoot(GameObjectHandler* handler);
        void tick();
        FloatUpdate* update(const int id);
        ~Sniper();
};

class JumpingSniper : public Enemy {
    private:
        bool shield_on;
    public:
        explicit JumpingSniper(const std::vector<float>& position);
        void collide_with(Projectile* projectile);
        void shoot(GameObjectHandler* handler);
        void tick();
        FloatUpdate* update(const int id);
        ~JumpingSniper();
};

#endif //ENEMY_H
