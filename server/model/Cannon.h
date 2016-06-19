#ifndef AMMO_H
#define AMMO_H

#include <vector>
#include <string>
#include <utility>

#include "Position.h"
#include "Movable.h"
#include "GameObjectHandler.h"

#define PLASMA_NAME "Plasma"
#define BOMB_NAME "Bomb"
#define MAGNET_NAME "Magnet"
#define SPARK_NAME "Spark"
#define FIRE_NAME "Fire"
#define RING_NAME "Ring"
#define PELLET_NAME "Pellet"

class Enemy;
class Object;
class MegaMan;
class GameObjectHandler;

class Projectile : public ProjectileMovable {
    private:
        const std::string name;
        const int damage;
        bool dead;
        bool thrown_by_megaman;

    protected:
        int ticks;

    public:
        Projectile(const std::string& name,
                   int damage,
                   float velocity_x, float velocity_y,
                   const std::vector<float>& initial_position,
                   bool thrown_by_megaman);
        const std::string& get_name();
        int hit();
        void collide_with(Enemy* enemy);
        virtual void collide_with(Object* object);
        virtual void collide_with(Projectile* projectile);
        void collide_with(Boss* boss);
        void collide_with(MegaMan* mm);
        void execute_collision_with(GameObject* other);
        void acknowledge_tick();
        virtual void tick() = 0;
        bool is_dead();
        bool was_thrown_by_megaman();
        std::pair<std::string, std::string> info(const int id);
        FloatUpdate* update(const int id);
        virtual ~Projectile();
};

class Plasma : public Projectile {
    public:
        Plasma(int damage, float velocity_x, float velocity_y,
               const std::vector<float>& initial_position);
        void tick();
};

class Bomb : public Projectile {
    private:
        bool has_bounced;
    public:
        Bomb(int damage, float velocity_x, float velocity_y,
             const std::vector<float>& initial_position,
             bool thrown_by_megaman);
        void collide_with(Object* object);
        void tick();
};

class Magnet : public Projectile {
    private:
        std::vector<float> target_position;
    public:
        Magnet(int damage, float velocity_x, float velocity_y,
               const std::vector<float>& initial_position,
               const std::vector<float>& target_position,
               bool thrown_by_megaman);
        void tick();
};

class Spark : public Projectile {
    private:
        static int spark_number;
    public:
        Spark(int damage, float velocity_x, float velocity_y,
              const std::vector<float>& initial_position,
              bool thrown_by_megaman);
        void tick();
};

class Fire : public Projectile {
    public:
        Fire(int damage, float velocity_x, float velocity_y,
             const std::vector<float>& initial_position,
             bool thrown_by_megaman);
        void tick();
};

class Ring : public Projectile {
    private:
        static int ring_number;
    public:
        Ring(int damage, float velocity_x, float velocity_y,
             const std::vector<float>& initial_position,
             bool thrown_by_megaman);
        void collide_with(Object* object);
        void collide_with(Projectile* projectile);
        void tick();
};

class Pellet : public Projectile {
    public:
        Pellet(float velocity_x, float velocity_y,
             const std::vector<float>& initial_position);
        void tick();
};

class Ammo {
    protected:
        const std::string name;
        const int max;
        int quantity;

    public:
        Ammo(const std::string& name, int max);
        virtual void use(GameObjectHandler* handler,
                        const std::vector<float>& position);
        virtual ~Ammo();
};

class MagnetAmmo : public Ammo {
    public:
        MagnetAmmo(const std::string& name, int max);
        void use(GameObjectHandler* handler, const std::vector<float>& position);
};

class Cannon {
    private:
        std::vector<Ammo*> ammos;
        Ammo* current_ammo;

    public:
        Cannon();
        void receive_new_ammo(std::string& name);
        void change_current_ammo(unsigned int ammo_id);
        void shoot(GameObjectHandler* handler,
                   const std::vector<float>& position);
        ~Cannon();
};


class CannonError : public SystemError {
public:
    explicit CannonError(const std::string error_msg) throw();
};

#endif //AMMO_H
