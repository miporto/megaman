#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <extern/libjson/json.hpp>

#include "common/Position.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1
#define DIRECTION_X_POS 2
#define DIRECTION_Y_POS 3

#define BODY_SIDE 50

using json = nlohmann::json;

class GameObject {
    private:
        const int side;

    protected:
        Position position;

    public:
        explicit GameObject(const std::vector<int>& position);
        GameObject(const int x, const int y);
        virtual void tick() = 0;
        virtual bool is_dead() = 0;
        virtual const std::string& get_name() = 0;
        virtual std::string info() = 0;
        virtual std::vector<int> get_position();
        virtual ~GameObject();
};

#endif //GAMEOBJECT_H
