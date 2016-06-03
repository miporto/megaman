#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

#include "GameObject.h"
#include "common/Position.h"

#define BLOCK_NAME "Block"
#define STAIRS_NAME "Stairs"
#define SPIKE_NAME "Spike"
#define CLIFF_NAME "Cliff"

class Enemy;
class Projectile;
class MegaMan;

class Object : public GameObject {
    private:
        const std::string name;

    public:
        Object(const std::string& name, const std::vector<int>& position);
        const std::string& get_name();
        void tick();
        std::string info();
        bool is_dead();
        void collide_with(Enemy* enemy);
        void collide_with(Object* object);
        void collide_with(Projectile* projectile);
        virtual void collide_with(MegaMan* mm) = 0;
        void execute_collision_with(GameObject* other);
        virtual ~Object();
};

class Stairs : public Object {
    public:
        explicit Stairs(const std::vector<int>& position);
        void collide_with(MegaMan* mm);
        ~Stairs();
};

class Spike : public Object {
    public:
        explicit Spike(const std::vector<int>& position);
        void collide_with(MegaMan* mm);
        ~Spike();
};

class Block : public Object {
    public:
        explicit Block(const std::vector<int>& position);
        void collide_with(MegaMan* mm);
        ~Block();
};

class Cliff : public Object {
    public:
        explicit Cliff(const std::vector<int>& position);
        void collide_with(MegaMan* mm);
        ~Cliff();
};

#endif //OBJECT_H
