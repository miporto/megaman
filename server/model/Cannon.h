#ifndef AMMO_H
#define AMMO_H

#include <vector>
#include <string>
#include <utility>

#include "common/Position.h"

class Projectile {
    protected:
        const int damage;
        const int velocity;
        Position position;

    public:
        Projectile(int damage,
                   int velocity,
                   Position& initial_position);
        virtual void tick() = 0;
        std::vector<int> get_position();
        virtual ~Projectile();
};

class Plasma : public Projectile {
    public:
        Plasma(int damage, int velocity, Position& initial_position);
        void tick();
};

class Bomb : public Projectile {
    public:
        Bomb(int damage, int velocity, Position& initial_position);
        void tick();
};

class Magnet : public Projectile {
    public:
        Magnet(int damage, int velocity, Position& initial_position);
        void tick();
};

class Spark : public Projectile {
    public:
        Spark(int damage, int velocity, Position& initial_position);
        void tick();
};

class Fire : public Projectile {
    public:
        Fire(int damage, int velocity, Position& initial_position);
        void tick();
};

class Ring : public Projectile {
    public:
        Ring(int damage, int velocity, Position& initial_position);
        void tick();
};

class Ammo {
    protected:
        const std::string name;
        const int max;
        int quantity;

    public:
        Ammo(std::string& name, int max);
        Projectile* use(Position& position);
        ~Ammo();
};

class Cannon {
    private:
        std::vector<Ammo*> ammos;
        Ammo* current_ammo;

    public:
        Cannon();
        void receive_new_ammo(std::string& name);
        void change_current_ammo(unsigned int ammo_id);
        Projectile* shoot(Position& position);
        ~Cannon();
};

#endif //AMMO_H
