#ifndef GAMEOBJECTHANDLER_H
#define GAMEOBJECTHANDLER_H

#include <map>
#include <vector>
#include <string>

#include "GameObject.h"

class GameObjectHandler {
    private:
        static unsigned int objects_count;
        std::map<GameObject*, int> object_id;
    protected:
        std::vector<GameObject*> objects;

        float dist(const std::vector<float>& position,
             const std::vector<float>& other_position);

    public:
        void set(const std::string& info);
        void add_game_object(GameObject* object);
        const std::string status();
        void tick();
        void check_collisions();
        std::vector<int> get_rid_of_corpses();
        virtual void spawn_powerup(const std::vector<float> initial_position);
        void create_new_projectiles();
        std::vector<FloatUpdate*> updates();
        std::vector<float> closest_enemy_for_megaman
                (const std::vector<float>& position);
        std::vector<float> closest_megaman(const std::vector<float>& position);
        virtual ~GameObjectHandler();
};

#endif //GAMEOBJECTHANDLER_H
