#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <Box2D/Dynamics/b2Body.h>

#include "common/Position.h"

class GameObject {
    private:
        b2Body* body;

        //void create_fixture();

    protected:
        Position position;
        //void set_bullet(bool option);

    public:
        explicit GameObject(const std::vector<int>& position);
        GameObject(const int x, const int y, const int direction);
        //virtual void set_body(b2Body* body);
        std::vector<int> get_position();
        virtual ~GameObject();
};

#endif //GAMEOBJECT_H
