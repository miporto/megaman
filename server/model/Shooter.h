#ifndef SHOOTER_H
#define SHOOTER_H

#include "Cannon.h"

class Shooter {
    public:
        virtual Projectile* shoot() = 0;
        virtual ~Shooter() {}
};

#endif //SHOOTER_H
