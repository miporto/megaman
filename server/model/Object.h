#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

#include "common/Position.h"
#include "GameObject.h"
#include "MegaMan.h"

#define BLOCK_NAME "Block"
#define STAIRS_NAME "Stairs"
#define SPIKE_NAME "Spike"
#define CLIFF_NAME "Cliff"

class Object : public GameObject {
    private:
        const std::string name;
    public:
        Object(const std::string& name, const std::vector<int>& position);
        const std::string& get_name();
        virtual void interact(MegaMan& mm) = 0;
        void tick();
        std::string info();
        bool is_dead();
        virtual ~Object();
};

class Stairs : public Object {
    public:
        explicit Stairs(const std::vector<int>& position);
        void interact(MegaMan& mm);
        ~Stairs();
};

class Spike : public Object {
    public:
        explicit Spike(const std::vector<int>& position);
        void interact(MegaMan& mm);
        ~Spike();
};

class Block : public Object {
    public:
        explicit Block(const std::vector<int>& position);
        void interact(MegaMan& mm);
        ~Block();
};

class Cliff : public Object {
    public:
        explicit Cliff(const std::vector<int>& position);
        void interact(MegaMan& mm);
        ~Cliff();
};

#endif //OBJECT_H
