#include <utility>
#include <map>
#include <vector>
#include <string>

#include "server/communication/InfoMaker.h"
#include "Map.h"
#include "Factory.h"
#include "GameObjectSetter.h"
#include "Enemy.h"

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

Map::~Map() {}
