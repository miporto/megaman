#ifndef OBJECT_H
#define OBJECT_H

class Object {
    private:
        const char position;

    public:
        explicit Object(const char position);
        virtual ~Object();
};

class Stairs : public Object {
    public:
        explicit Stairs(const char position);
        ~Stairs();
};

class Spike : public Object {
    public:
        explicit Spike(const char position);
        ~Spike();
};

class Block : public Object {
    public:
        explicit Block(const char position);
        ~Block();
};

#endif //OBJECT_H
