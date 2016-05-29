#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "common/Position.h"
#include "MegaMan.h"

class Object {
    protected:
        const Position position;

    public:
        explicit Object(const std::vector<int>& position);
        virtual void interact(MegaMan& mm) = 0;
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
