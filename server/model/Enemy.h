#ifndef ENEMY_H
#define ENEMY_H

#include <utility>

#include "common/Position.h"
#include "Cannon.h"
#include "Mortal.h"
#include "Shooter.h"

class Enemy : public Mortal, public Shooter {
    protected:
        Position position;
        int energy;
    public:
        Enemy(int x, int y, int energy);
        void decrease_energy(int amount);
        bool is_dead();
        virtual Projectile* shoot() = 0;
        virtual Projectile* tick() = 0;
        std::pair<int, int> get_position();
        virtual ~Enemy();
};

class Met : public Enemy {
    private:
        const int velocity;
    public:
        Met(int x, int y);
        Projectile* shoot();
        Projectile* tick();
        ~Met();
};

class Bumby : public Enemy {
    private:
        const int velocity;
    public:
        Bumby(int x, int y);
        Projectile* shoot();
        Projectile* tick();
        ~Bumby();
};

class Sniper : public Enemy {
    private:
        const int velocity;
    public:
        Sniper(int x, int y);
        Projectile* shoot();
        Projectile* tick();
        ~Sniper();
};

class JumpingSniper : public Enemy {
    private:
        const int velocity;
    public:
        JumpingSniper(int x, int y);
        Projectile* shoot();
        Projectile* tick();
        ~JumpingSniper();
};

#endif //ENEMY_H
