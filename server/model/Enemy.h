#ifndef ENEMY_H
#define ENEMY_H

#include <vector>

#include "common/Position.h"
#include "Cannon.h"
#include "Mortal.h"

class Enemy : public Movable {
    private:
        int energy;
    public:
        Enemy(const std::vector<int>& position, const int velocity, int energy);
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
