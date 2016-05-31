#include <vector>
#include <string>
#include <server/communication/TickInfoMaker.h>

#include "Map.h"
#include "Factory.h"
#include "ServerStageSetter.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1

#define PIXELS_PER_METER 32.0f
#define GRAVITY_DENOM 0.7f

void Map::create_physical_world() {
    this->world.SetAllowSleeping(true);
    this->world.SetContinuousPhysics(true);
    //this->world.SetContactListener(this);
}

Map::Map() : world(b2Vec2(0.0f, PIXELS_PER_METER / GRAVITY_DENOM)),
             width(MapFactory::width()), height(MapFactory::height()) {
    this->create_physical_world();
}

void Map::add_body(GameObject* object) {
    std::vector<int> position = object->get_position();
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(
            position[X_COORD_POS] / PIXELS_PER_METER,
            position[Y_COORD_POS] / PIXELS_PER_METER);
    bodyDef.userData = object;
    bodyDef.fixedRotation = true;
    object->set_body(this->world.CreateBody(&bodyDef));
}

void Map::add_player(Player* player) {
    this->players.push_back(player);
    //TODO this->add_body(megaman);
}

void Map::set(const std::string& info) {
    ServerStageSetter setter(info, this);
}

void Map::add_enemy(Enemy* enemy) {
    this->enemies.push_back(enemy);
    this->add_body(enemy);
}

void Map::add_object(Object* object) {
    this->objects.push_back(object);
    this->add_body(object);
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
