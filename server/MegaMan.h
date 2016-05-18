#ifndef MEGAMAN_H
#define MEGAMAN_H

#include <vector>

class Ammo {
private:
    const int max;
    const int damage;
    const int vel;
    int quantity;

public:
    Ammo();
    void use();
    ~Ammo();
};

class Cannon {
    private:
        std::vector<Ammo> ammos;

    public:
        Cannon();
        ~Cannon();
};

class EnergyTank {
    private:
        int lives;
        const int max_energy;
        int current_energy;

        void reset();

    public:
        EnergyTank();
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
        MegaMan();
        ~MegaMan();
};


#endif //MEGAMAN_H
