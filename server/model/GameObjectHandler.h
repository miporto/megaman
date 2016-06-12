#ifndef GAMEOBJECTHANDLER_H
#define GAMEOBJECTHANDLER_H

#include <map>
#include <vector>
#include <string>

#include "GameObject.h"

class GameObjectHandler {
    private:
        std::vector<GameObject*> objects;
        std::map<GameObject*, int> object_id;

    public:
        void set(const std::string& info);
        void add_game_object(GameObject* object);
        const std::string status();
        void tick();
        void check_collisions();
        std::vector<int> get_rid_of_corpses();
        void create_new_projectiles();
        std::vector<FloatUpdate*> updates();
        virtual ~GameObjectHandler();
};

#endif //GAMEOBJECTHANDLER_H
