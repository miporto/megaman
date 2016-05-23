#ifndef TICKABLE_H
#define TICKABLE_H

class Tickable {
    public:
        virtual void tick() = 0;
        virtual ~Tickable() {}
};

#endif //TICKABLE_H
