#ifndef MEGAMAN_H
#define MEGAMAN_H

class Cannon {

};

class EnergyTank {
    private:
        int lives;
        const int max_energy;
        int current_energy;
    public:
        EnergyTank();
        void increase_energy(int amount);
        void decrease_energy(int amount);
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
