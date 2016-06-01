#ifndef AMMO_H
#define AMMO_H

#include <vector>
#include <string>
#include <utility>

#include "common/Position.h"
#include "Movable.h"

#define PLASMA_NAME "plasma"
#define BOMB_NAME "bomb"
#define MAGNET_NAME "magnet"
#define SPARK_NAME "spark"
#define FIRE_NAME "fire"
#define RING_NAME "ring"

class Projectile : public Movable {
    private:
        const std::string name;
        const int damage;

    public:
        Projectile(const std::string& name,
                   int damage,
                   int velocity,
                   const std::vector<int>& initial_position);
        virtual void tick() = 0;
        const std::string& get_name();
        virtual ~Projectile();
};

class Plasma : public Projectile {
    public:
        Plasma(int damage, int velocity,
               const std::vector<int>& initial_position);
        void tick();
};

class Bomb : public Projectile {
    public:
        Bomb(int damage, int velocity,
             const std::vector<int>& initial_position);
        void tick();
};

class Magnet : public Projectile {
    public:
        Magnet(int damage, int velocity,
               const std::vector<int>& initial_position);
        void tick();
};

class Spark : public Projectile {
    public:
        Spark(int damage, int velocity,
              const std::vector<int>& initial_position);
        void tick();
};

class Fire : public Projectile {
    public:
        Fire(int damage, int velocity,
             const std::vector<int>& initial_position);
        void tick();
};

class Ring : public Projectile {
    public:
        Ring(int damage, int velocity,
             const std::vector<int>& initial_position);
        void tick();
};

class Ammo {
    protected:
        const std::string name;
        const int max;
        int quantity;

    public:
        Ammo(const std::string& name, int max);
        Projectile* use(const std::vector<int>& position);
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
        Projectile* shoot(const std::vector<int>& position);
        ~Cannon();
};

#endif //AMMO_H
