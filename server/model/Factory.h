#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <string>
#include <map>

#include "extern/libjson/json.hpp"
#include "Cannon.h"

using json = nlohmann::json;

class EnemyFactory {
public:
    static int energy(std::string name);
    static int velocity(std::string name);
    ~EnemyFactory();
};

class MegaManFactory {
    public:
        static int velocity();
        ~MegaManFactory();
};

class EnergyTankFactory {
    public:
        static int initial_lives();
        static int maximum_energy();
        ~EnergyTankFactory();
};

class ProjectileFactory {
    public:
        static Projectile* projectile
                (const std::string& name, const std::vector<int>& position);
        ~ProjectileFactory();
};

class AmmoFactory {
    public:
        static Ammo* ammo(const std::string& name);
        ~AmmoFactory();
};

typedef std::vector<std::vector<int>> StageFactoryPositions;
typedef std::map<std::string,
        std::vector<std::vector<int>>> StageFactoryInfo;

class StageFactory {
    public:
        static const std::string initial_stage(const char stage_id);
        ~StageFactory();
};

class MapFactory {
    public:
        static unsigned int width();
        static unsigned int height();
        ~MapFactory();
};

#endif //FACTORY_H
