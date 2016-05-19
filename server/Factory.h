#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <string>

#include "common/ScreenInfo.h"
#include "Cannon.h"

class EnergyTankFactory {
    public:
        int initial_lives();
        int maximum_energy();
        ~EnergyTankFactory();
};

class ProjectileFactory {
    public:
        Projectile* operator()(const std::string& name, Position& position);
        ~ProjectileFactory();
};

class AmmoFactory {
    public:
        Ammo* operator()(const std::string& name);
        ~AmmoFactory();
};

class StageFactory {
private:
    const char id;

    std::vector<char> positions_of_spawns
            (const int screen, const int enemy_id);
    std::vector<char> positions_of_objects
            (const int screen, const int object_id);

public:
    explicit StageFactory(char id);
    ScreenInfo* screen_info(const int screen);
    ~StageFactory();
};

#endif //FACTORY_H
