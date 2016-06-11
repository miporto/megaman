#ifndef MEGAMAN_H
#define MEGAMAN_H

#include <utility>
#include <vector>
#include <string>

#include "Position.h"
#include "Movable.h"
#include "Cannon.h"

class EnergyTank {
    private:
        int lives;
        const int max_energy;
        int current_energy;

    public:
        EnergyTank();
        void increase_energy(int amount);
        void decrease_energy(int amount);
        void reset();
        bool is_empty();
        int get_energy();
        ~EnergyTank();
};

class MegaMan : public UserMovable {
    private:
        const std::string& name;
        EnergyTank tank;
        Cannon cannon;

    public:
        explicit MegaMan(const std::string& name);
        const std::string& get_name();
        void decrease_energy(int amount);
        int get_energy();
        void kill();
        Projectile* shoot();
        void collide_with(Enemy* enemy);
        void collide_with(Object* object);
        void collide_with(Projectile* projectile);
        void collide_with(MegaMan* mm);
        void execute_collision_with(GameObject* other);
        void change_ammo(unsigned int ammo_id);
        void receive_new_ammo(std::string& name);
        void tick();
        bool is_dead();
        bool is_megaman();
        std::pair<std::string, std::string> info();
        ~MegaMan();
};


#endif //MEGAMAN_H
