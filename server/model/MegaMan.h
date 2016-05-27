#ifndef MEGAMAN_H
#define MEGAMAN_H

#include <vector>
#include <string>

#include "common/Position.h"
#include "Cannon.h"
#include "Mortal.h"

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
        ~EnergyTank();
};

class MegaMan : public Movable {
    private:
        EnergyTank tank;
        Cannon cannon;

    public:
        MegaMan();
        void decrease_energy(int amount);
        void kill();
        bool is_dead();
        Projectile* shoot();
        void change_ammo(unsigned int ammo_id);
        void receive_new_ammo(std::string& name);
        ~MegaMan();
};


#endif //MEGAMAN_H
