#ifndef GAMEOBJECTHANDLER_H
#define GAMEOBJECTHANDLER_H

#include <map>
#include <vector>

#include "GameObject.h"

class GameObjectHandler {
    protected:
        std::vector<GameObject*> objects;
        std::map<GameObject*, int> object_id;
    public:
        void add_game_object(GameObject* object);
        virtual ~GameObjectHandler();
};

#endif //GAMEOBJECTHANDLER_H
