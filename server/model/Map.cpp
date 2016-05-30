#include <vector>
#include <string>
#include <server/communication/TickInfoMaker.h>

#include "Map.h"
#include "Factory.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1

Map::Map() : //gravity(0.0f, -10.0f), world(this->gravity),
             width(MapFactory::width()), height(MapFactory::height()) {}

void Map::add_player(Player* player) {
    this->players.push_back(player);
}

void Map::set(const std::string& info) {
    //TODO parsear info con Factory y
    // setear objetos y enemigos en mundo de box2d?
}

void Map::tick() {
    for (unsigned int i = 0; i < this->enemies.size(); ++i)
        this->enemies[i]->tick();
    for (unsigned int i = 0; i < this->projectiles.size(); ++i)
        this->projectiles[i]->tick();
}

void Map::get_rid_of_corpses() {
    for (unsigned int i = 0; i < this->enemies.size(); ++i) {
        if (this->enemies[i]->is_dead()) {
            Enemy* dead_enemy = this->enemies[i];
            this->enemies.erase(this->enemies.begin() + i);
            delete dead_enemy;
        }
    }

    for (unsigned int i = 0; i < this->players.size(); ++i) {
        if (this->players[i]->is_dead()) {
            //Player* dead_player = this->players[i];
            //TODO Que se hace con jugadores muertos??
        }
    }

    //TODO loop para sacar proyectiles out of range?
}

const std::string Map::status() {
    TickInfoMaker info;
    for (unsigned int i = 0; i < this->players.size(); ++i)
        info.add_player(this->players[i]->get_name(),
                        this->players[i]->get_position(),
                        this->players[i]->get_energy());

    for (unsigned int i = 0; i < this->enemies.size(); ++i)
        info.add_enemy(this->enemies[i]->get_name(),
                       this->enemies[i]->get_position());

    for (unsigned int i = 0; i < this->projectiles.size(); ++i)
        info.add_projectile(this->projectiles[i]->get_name(),
                            this->projectiles[i]->get_position());

    return info.str();
}

Map::~Map() {
    for (unsigned int i = 0; i < this->enemies.size(); ++i)
        delete this->enemies[i];
    for (unsigned int i = 0; i < this->objects.size(); ++i)
        delete this->objects[i];
    for (unsigned int i = 0; i < this->projectiles.size(); ++i)
        delete this->projectiles[i];
}
