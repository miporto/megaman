#ifndef MEGAMAN_H
#define MEGAMAN_H

#include <utility>
#include <vector>
#include <string>

#include "Position.h"
#include "Movable.h"
#include "Cannon.h"

#define MEGAMAN_NAME "MegaMan"

class GameObjectHandler;

class EnergyTank {
    private:
        int lives;
        const int max_energy;
        int current_energy;
        int previous_energy;
        bool respawned;

    public:
        EnergyTank();
        void increase_energy(int amount);
        void decrease_energy(int amount);
        void reset();
        bool is_empty();
        int get_energy();
        float get_energy_percentage();
        bool just_respawned();
        bool energy_changed();
        ~EnergyTank();
};

class MegaMan : public UserMovable {
    private:
        const std::string& name;
        EnergyTank tank;
        Cannon cannon;

    public:
        explicit MegaMan(const std::string& name);
        const std::string& get_name();
        void decrease_energy(int amount);
        void kill();
        void shoot(GameObjectHandler* handler);
        void collide_with(Enemy* enemy);
        void collide_with(Object* object);
        void collide_with(Projectile* projectile);
        void collide_with(Boss* boss);
        void collide_with(MegaMan* mm);
        void execute_collision_with(GameObject* other);
        void change_ammo(unsigned int ammo_id);
        void receive_new_ammo(std::string& name);
        void tick();
        bool is_dead();
        std::pair<std::string, std::string> info(const int id);
        bool energy_changed();
        FloatUpdate* update(const int id);
        bool is_megaman();
        ~MegaMan();
};


#endif //MEGAMAN_H
