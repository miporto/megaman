#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <string>

#include "common/Position.h"
#include "Cannon.h"
#include "Mortal.h"

#define MET_NAME "met"
#define BUMBY_NAME "bumby"
#define SNIPER_NAME "sniper"
#define JUMPING_SNIPER_NAME "jumping sniper"

class Enemy : public Movable {
    private:
        const std::string name;
        int energy;
    public:
        Enemy(const std::string& name, const std::vector<int>& position,
              const int velocity, int energy);
        const std::string& get_name();
        void decrease_energy(int amount);
        bool is_dead();
        virtual Projectile* shoot() = 0;
        virtual Projectile* tick() = 0;
        virtual ~Enemy();
};

class Met : public Enemy {
    public:
        explicit Met(const std::vector<int>& position);
        Projectile* shoot();
        Projectile* tick();
        ~Met();
};

class Bumby : public Enemy {
    public:
        explicit Bumby(const std::vector<int>& position);
        Projectile* shoot();
        Projectile* tick();
        ~Bumby();
};

class Sniper : public Enemy {
    public:
        explicit Sniper(const std::vector<int>& position);
        Projectile* shoot();
        Projectile* tick();
        ~Sniper();
};

class JumpingSniper : public Enemy {
    public:
        explicit JumpingSniper(const std::vector<int>& position);
        Projectile* shoot();
        Projectile* tick();
        ~JumpingSniper();
};

#endif //ENEMY_H
