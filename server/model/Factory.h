#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <string>

#include "common/communication/StageInfo.h"
#include "Cannon.h"

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

class StageFactory {
    private:
        std::vector<Position*> positions_of_spawns
                (const int stage_id, const int enemy_id);
        std::vector<Position*> positions_of_objects
                (const int stage_id, const int object_id);

    public:
        static StageInfo* stage_info(const int stage_id);
        ~StageFactory();
};

class MapFactory {
    public:
        static unsigned int width();
        static unsigned int height();
        ~MapFactory();
};

#endif //FACTORY_H
