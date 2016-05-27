#ifndef ENEMY_H
#define ENEMY_H

#include <vector>

#include "common/Position.h"
#include "Cannon.h"
#include "Mortal.h"
#include "Shooter.h"

class Enemy : public Mortal, public Shooter {
    protected:
        Position position;
        int energy;

    public:
        Enemy(const std::vector<int>& position, int energy);
        void decrease_energy(int amount);
        bool is_dead();
        virtual Projectile* shoot() = 0;
        virtual Projectile* tick() = 0;
        std::vector<int> get_position();
        virtual ~Enemy();
};

class Met : public Enemy {
    private:
        const int velocity;
    public:
        explicit Met(const std::vector<int>& position);
        Projectile* shoot();
        Projectile* tick();
        ~Met();
};

class Bumby : public Enemy {
    private:
        const int velocity;
    public:
        explicit Bumby(const std::vector<int>& position);
        Projectile* shoot();
        Projectile* tick();
        ~Bumby();
};

class Sniper : public Enemy {
    private:
        const int velocity;
    public:
        explicit Sniper(const std::vector<int>& position);
        Projectile* shoot();
        Projectile* tick();
        ~Sniper();
};

class JumpingSniper : public Enemy {
    private:
        const int velocity;
    public:
        explicit JumpingSniper(const std::vector<int>& position);
        Projectile* shoot();
        Projectile* tick();
        ~JumpingSniper();
};

#endif //ENEMY_H
