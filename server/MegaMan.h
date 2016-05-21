#ifndef MEGAMAN_H
#define MEGAMAN_H

#include <vector>
#include <string>

#include "common/Position.h"
#include "Cannon.h"

class EnergyTank {
    private:
        int lives;
        int max_energy;
        int current_energy;

    public:
        EnergyTank();
        void increase_energy(int amount);
        void decrease_energy(int amount);
        void reset();
        bool is_empty();
        ~EnergyTank();
};

class MegaMan {
    friend class Object;

    private:
        EnergyTank tank;
        Cannon cannon;
        Position position;

    public:
        MegaMan();
        void decrease_energy(int amount);
        void kill();
        bool is_dead();
        Projectile* shoot();
        void change_ammo(unsigned int ammo_id);
        void receive_new_ammo(std::string& name);
        //x_amount y y_amount tienen que venir con sentido,
        // ej: si retrocede x_amount es negativo
        void move(int x_amount, int y_amount);
        Position& get_position();
        ~MegaMan();
};


#endif //MEGAMAN_H
