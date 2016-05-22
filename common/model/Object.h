#ifndef OBJECT_H
#define OBJECT_H

#include "Position.h"
#include "MegaMan.h"

class Object {
    protected:
        const Position position;

    public:
        Object(const int x, const int y);
        virtual void interact(MegaMan& mm) = 0;
        virtual ~Object();
};

class Stairs : public Object {
    public:
        Stairs(const int x, const int y);
        void interact(MegaMan& mm);
        ~Stairs();
};

class Spike : public Object {
    public:
        Spike(const int x, const int y);
        void interact(MegaMan& mm);
        ~Spike();
};

class Block : public Object {
    public:
        Block(const int x, const int y);
        void interact(MegaMan& mm);
        ~Block();
};

class Cliff : public Object {
    public:
        Cliff(const int x, const int y);
        void interact(MegaMan& mm);
        ~Cliff();
};

#endif //OBJECT_H
