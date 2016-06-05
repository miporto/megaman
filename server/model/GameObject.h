#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <extern/libjson/json.hpp>

#include "common/Position.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1
#define DIRECTION_X_POS 2
#define DIRECTION_Y_POS 3

#define BODY_SIDE 1

using json = nlohmann::json;

class Enemy;
class Object;
class Projectile;
class MegaMan;

class GameObject {
    private:
        const int side;
    protected:
        Position position;

    public:
        explicit GameObject(const std::vector<float>& position);
        GameObject(const float x, const float y);
        virtual const std::string& get_name() = 0;
        int get_side();
        virtual std::vector<float> get_position();
        bool collided_with(GameObject* other);
        virtual void collide_with(Enemy* enemy) = 0;
        virtual void collide_with(Object* object) = 0;
        virtual void collide_with(Projectile* projectile) = 0;
        virtual void collide_with(MegaMan* mm) = 0;
        virtual void execute_collision_with(GameObject* other) = 0;
        virtual void tick() = 0;
        virtual bool is_dead() = 0;
        virtual bool is_enemy() = 0;
        virtual std::string info() = 0;
        virtual ~GameObject();
};

#endif //GAMEOBJECT_H
