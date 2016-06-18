#include <utility>
#include <map>
#include <vector>
#include <string>

#include "server/communication/InfoMaker.h"
#include "Map.h"
#include "Factory.h"
#include "GameObjectSetter.h"
#include "Enemy.h"
#include "PowerUp.h"

#define EXTRALIFE_PROBABILITY 1
#define EXTRAENERGY_PROBABILITY 10
#define EXTRAPLASMA_PROBABILITY 5

Map::Map() : width(MapFactory::width()), height(MapFactory::height()) {}

void Map::release_megamen() {
    for (std::vector<GameObject*>::iterator it = this->objects.begin();
        it != this->objects.end();) {
        if ((*it)->is_megaman())
            it = this->objects.erase(it);
        else
            ++it;
    }
}

void Map::spawn_powerup(const std::vector<float> initial_position) {
    int number = 100;//rand() % 100 + 1;
    if (number <= EXTRALIFE_PROBABILITY)
        this->add_game_object(new ExtraLife(initial_position));
    else if (number <= EXTRAENERGY_PROBABILITY)
        this->add_game_object(new ExtraEnergy(initial_position));
    else if (number <= EXTRAPLASMA_PROBABILITY)
        this->add_game_object(new ExtraPlasma(initial_position));
}


Map::~Map() {}
