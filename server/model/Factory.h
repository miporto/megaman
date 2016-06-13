#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <string>
#include <map>

#include "extern/libjson/json.hpp"
#include "Cannon.h"
#include "Boss.h"

using json = nlohmann::json;

class FileReader {
    public:
        static json read(const std::string& file_name,
                         const std::string& branch_name);
        ~FileReader();
};

class EnemyFactory {
    public:
        static int energy(const std::string& name);
        static float velocity_x(const std::string& name);
        static float velocity_y(const std::string& name);
        ~EnemyFactory();
};

class MegaManFactory {
    public:
        static std::vector<float> respawn_point();
        static float velocity_x();
        static float velocity_y();
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
                (const std::string& name, const std::vector<float>& position);
        ~ProjectileFactory();
};

class AmmoFactory {
    public:
        static Ammo* ammo(const std::string& name);
        ~AmmoFactory();
};

class BossFactory {
    public:
        static Boss* boss(const char stage_id);
        ~BossFactory();
};

class StageFactory {
    public:
        static const std::string initial_stage(const char stage_id);
        ~StageFactory();
};

class BossChamberFactory {
    public:
        static const std::string chamber();
        ~BossChamberFactory();
};

class MapFactory {
    public:
        static unsigned int width();
        static unsigned int height();
        ~MapFactory();
};

class FactoryError : public SystemError {
public:
    explicit FactoryError(const std::string error_msg) throw();
};

#endif //FACTORY_H
