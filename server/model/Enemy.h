#ifndef ENEMY_H
#define ENEMY_H

#include <utility>
#include <vector>
#include <string>

#include "common/Position.h"
#include "Movable.h"

#define MET_NAME "Met"
#define BUMBY_NAME "Bumby"
#define SNIPER_NAME "Sniper"
#define JUMPING_SNIPER_NAME "JumpingSniper"

class Map;
class Object;
class Projectile;
class MegaMan;

class Enemy : public Movable {
    private:
        const std::string name;
        int energy;

    public:
        Enemy(const std::string& name, const std::vector<float>& position,
              const float velocity_x, const float velocity_y, int energy);
        const std::string& get_name();
        void decrease_energy(int amount);
        bool is_dead();
        void collide_with(Enemy* enemy);
        void collide_with(Object* object);
        virtual void collide_with(Projectile* projectile) = 0;
        void collide_with(MegaMan* mm);
        void execute_collision_with(GameObject* other);
        virtual void shoot(Map* map) = 0;
        virtual void tick() = 0;
        bool is_enemy();
        std::pair<std::string, std::string> info(const int id);
        virtual ~Enemy();
};

class Met : public Enemy {
    private:
        int ticks;
        bool helmet_on;
    public:
        explicit Met(const std::vector<float>& position);
        void collide_with(Projectile* projectile);
        void shoot(Map* map);
        void tick();
        ~Met();
};

class Bumby : public Enemy {
    private:
        int ticks;
    public:
        explicit Bumby(const std::vector<float>& position);
        void collide_with(Projectile* projectile);
        void shoot(Map* map);
        void tick();
        ~Bumby();
};

class Sniper : public Enemy {
    private:
        int ticks;
        bool shield_on;
    public:
        explicit Sniper(const std::vector<float>& position);
        void collide_with(Projectile* projectile);
        void shoot(Map* map);
        void tick();
        ~Sniper();
};

class JumpingSniper : public Enemy {
    private:
        int ticks;
        bool shield_on;
    public:
        explicit JumpingSniper(const std::vector<float>& position);
        void collide_with(Projectile* projectile);
        void shoot(Map* map);
        void tick();
        ~JumpingSniper();
};

#endif //ENEMY_H
