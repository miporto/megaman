#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>

#include "common/Position.h"

#define BODY_SIDE 50

class GameObject {
    private:
        const int side;

    protected:
        Position position;

    public:
        explicit GameObject(const std::vector<int>& position);
        GameObject(const int x, const int y);
        std::vector<int> get_position();
        virtual ~GameObject();
};

#endif //GAMEOBJECT_H
