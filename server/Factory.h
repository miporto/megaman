#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <string>

#include "extern/json.hpp"
#include "common/StageInfo.h"
#include "common/model/Cannon.h"

using json = nlohmann::json;

class EnergyTankFactory {
    private:
        json info;

    public:
        EnergyTankFactory();
        int initial_lives();
        int maximum_energy();
        ~EnergyTankFactory();
};

class ProjectileFactory {
    private:
        json info;

    public:
        ProjectileFactory();
        Projectile* operator()(const std::string& name, Position& position);
        ~ProjectileFactory();
};

class AmmoFactory {
    private:
        json info;

    public:
        AmmoFactory();
        Ammo* operator()(const std::string& name);
        ~AmmoFactory();
};

class StageFactory {
    private:
        std::vector<Position*> positions_of
                (const char* type, const int enemy_id);
        json stage_json;

    public:
        StageInfo* operator()(const int stage_id);
        ~StageFactory();
};

#endif //FACTORY_H
