#ifndef GAMEOBJECTHANDLER_H
#define GAMEOBJECTHANDLER_H

#include <map>
#include <vector>
#include <string>

#include "GameObject.h"

class GameObjectHandler {
    protected:
        std::vector<GameObject*> objects;
        std::map<GameObject*, int> object_id;
    public:
        void set(const std::string& info);
        void add_game_object(GameObject* object);
        const std::string status();
        void tick();
        void check_collisions();
        virtual ~GameObjectHandler();
};

#endif //GAMEOBJECTHANDLER_H
