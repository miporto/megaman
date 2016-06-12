#ifndef SHOOTER_H
#define SHOOTER_H

class GameObjectHandler;

class Shooter {
    public:
        virtual void shoot(GameObjectHandler* handler) = 0;
};

#endif //SHOOTER_H
