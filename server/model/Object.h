#ifndef OBJECT_H
#define OBJECT_H

#include <utility>
#include <string>
#include <vector>
#include <common/SystemError.h>

#include "GameObject.h"
#include "Position.h"

#define BLOCK_NAME "Block"
#define STAIRS_NAME "Stairs"
#define SPIKE_NAME "Spike"
#define CLIFF_NAME "Cliff"
#define DOOR_NAME "Door"

class Enemy;
class Projectile;
class MegaMan;

class Object : public GameObject {
    private:
        const std::string name;

    public:
        Object(const std::string& name, const std::vector<float>& position);
        const std::string& get_name();
        void collide_with(Enemy* enemy);
        void collide_with(Object* object);
        void collide_with(Projectile* projectile);
        virtual void collide_with(MegaMan* mm) = 0;
        void execute_collision_with(GameObject* other);
        void tick();
        bool is_dead();
        bool is_enemy();
        std::pair<std::string, std::string> info();
        virtual ~Object();
};

class Stairs : public Object {
    public:
        explicit Stairs(const std::vector<float>& position);
        void collide_with(MegaMan* mm);
        ~Stairs();
};

class Spike : public Object {
    public:
        explicit Spike(const std::vector<float>& position);
        void collide_with(MegaMan* mm);
        ~Spike();
};

class Block : public Object {
    public:
        explicit Block(const std::vector<float>& position);
        void collide_with(MegaMan* mm);
        ~Block();
};

class Cliff : public Object {
    public:
        explicit Cliff(const std::vector<float>& position);
        void collide_with(MegaMan* mm);
        ~Cliff();
};

class Door : public Object {
public:
    explicit Door(const std::vector<float>& position);
    void collide_with(MegaMan* mm);
    ~Door();
};

class ObjectError : public SystemError {
public:
    explicit ObjectError(const std::string error_msg) throw();
};

#endif //OBJECT_H
