#ifndef SHOOTER_H
#define SHOOTER_H

class Shooter {
    public:
        virtual void shoot(GameObjectHandler* handler) = 0;
};

#endif //SHOOTER_H
