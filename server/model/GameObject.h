#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <utility>
#include <vector>
#include <string>
#include <extern/libjson/json.hpp>

#include "Position.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1
#define DIRECTION_X_POS 2
#define DIRECTION_Y_POS 3

#define BODY_SIDE 1

using json = nlohmann::json;

class Enemy;
class Object;
class Projectile;
class Boss;
class MegaMan;
class FloatUpdate;

class GameObject {
    private:
        const float side;

    protected:
        Position position;

    public:
        explicit GameObject(const std::vector<float>& position,
                            const float side);
        GameObject(const float x, const float y, const float side);
        virtual const std::string& get_name() = 0;
        float get_side();
        virtual std::vector<float> get_position();
        bool collided_with(GameObject* other);
        virtual void collide_with(Enemy* enemy) = 0;
        virtual void collide_with(Object* object) = 0;
        virtual void collide_with(Projectile* projectile) = 0;
        virtual void collide_with(Boss* boss) = 0;
        virtual void collide_with(MegaMan* mm) = 0;
        virtual void execute_collision_with(GameObject* other) = 0;
        virtual void tick() = 0;
        virtual bool is_dead() = 0;
        virtual bool it_moved();
        virtual std::pair<std::string, std::string> info(const int id) = 0;
        virtual FloatUpdate* update(const int id) = 0;
        virtual bool shoots_per_tick();
        virtual bool is_megaman();
        //
        virtual bool is_enemy();
        virtual bool is_boss();
        //
        virtual ~GameObject();
};

#endif //GAMEOBJECT_H
