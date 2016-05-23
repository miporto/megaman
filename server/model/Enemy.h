#ifndef ENEMY_H
#define ENEMY_H

#include "common/Position.h"
#include "Cannon.h"
#include "Mortal.h"
#include "Shooter.h"
#include "Tickable.h"

class Enemy : public Mortal, public Shooter, public Tickable {
    protected:
        Position position;
        int energy;
    public:
        Enemy(int x, int y, int energy);
        void decrease_energy(int amount);
        bool is_dead();
        virtual Projectile* shoot() = 0;
        virtual void tick() = 0;
        virtual ~Enemy();
};

class Met : public Enemy {
    private:
        const int velocity;
    public:
        Met(int x, int y);
        Projectile* shoot();
        void tick();
        ~Met();
};

class Bumby : public Enemy {
    private:
        const int velocity;
    public:
        Bumby(int x, int y);
        Projectile* shoot();
        void tick();
        ~Bumby();
};

class Sniper : public Enemy {
    private:
        const int velocity;
    public:
        Sniper(int x, int y);
        Projectile* shoot();
        void tick();
        ~Sniper();
};

class JumpingSniper : public Enemy {
    private:
        const int velocity;
    public:
        JumpingSniper(int x, int y);
        Projectile* shoot();
        void tick();
        ~JumpingSniper();
};

#endif //ENEMY_H
