#ifndef MEGAMAN_H
#define MEGAMAN_H

#include <vector>

#include "Cannon.h"

class EnergyTank {
    private:
        int lives;
        int max_energy;
        int current_energy;

        void reset();

    public:
        EnergyTank(int initial_lives, int max_energy);
        void increase_energy(int amount);
        void decrease_energy(int amount);
        bool is_empty();
        ~EnergyTank();
};

class MegaMan {
    private:
        EnergyTank tank;
        Cannon cannon;

    public:
        ~MegaMan();
};


#endif //MEGAMAN_H
