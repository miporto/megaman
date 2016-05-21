#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <string>

#include "common/StageInfo.h"
#include "common/model/Cannon.h"

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
        std::vector<char> positions_of_spawns
                (const int stage_id, const int enemy_id);
        std::vector<char> positions_of_objects
                (const int stage_id, const int object_id);

    public:
        StageInfo* operator()(const int stage_id);
        ~StageFactory();
};

#endif //FACTORY_H
