#ifndef AMMO_H
#define AMMO_H

#include <vector>
#include <string>
#include <utility>

#include "common/Position.h"
#include "Movable.h"

#define PLASMA_NAME "Plasma"
#define BOMB_NAME "Bomb"
#define MAGNET_NAME "Magnet"
#define SPARK_NAME "Spark"
#define FIRE_NAME "Fire"
#define RING_NAME "Ring"

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
        std::string info();
        bool is_dead();
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
