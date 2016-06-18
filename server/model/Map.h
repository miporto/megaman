#ifndef MAP_H
#define MAP_H

#include <map>
#include <vector>
#include <string>
#include <utility>

#include "common/communication/Packet.h"
#include "GameObject.h"
#include "GameObjectHandler.h"

class Map : public GameObjectHandler {
    private:
        const unsigned int width, height;

    public:
        Map();
        void release_megamen();
        void spawn_powerup(const std::vector<float> initial_position);
        ~Map();
};

#endif //MAP_H
