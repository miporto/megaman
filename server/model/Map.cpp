#include <vector>
#include <string>

#include "common/communication/StageInfo.h"
#include "Map.h"
#include "Factory.h"

#define X_COORD_POS 0
#define Y_COORD_POS 1

void Cell::add(Enemy* enemy) {
    this->enemies.push_back(enemy);
}

void Cell::add(Object* object) {
    this->objects.push_back(object);
}

void Cell::add(Projectile* projectile) {
    this->projectiles.push_back(projectile);
}

std::vector<Enemy*>& Cell::get_enemies() {
    return this->enemies;
}

std::vector<Projectile*>& Cell::get_projectiles() {
    return this->projectiles;
}

void Cell::get_rid_of_corpses() {
    for (unsigned int i = 0; i < this->enemies.size(); ++i) {
        if (this->enemies[i]->is_dead()) {
            Enemy* dead_enemy = this->enemies[i];
            this->enemies.erase(this->enemies.begin() + i);
            delete dead_enemy;
        }
    }
}

Cell::~Cell() {
    for (unsigned int i = 0; i < this->enemies.size(); ++i)
        delete this->enemies[i];
    for (unsigned int i = 0; i < this->objects.size(); ++i)
        delete this->objects[i];
    for (unsigned int i = 0; i < this->projectiles.size(); ++i)
        delete this->projectiles[i];
}

Map::Map() : //gravity(0.0f, -10.0f), world(this->gravity),
             width(MapFactory::width()), height(MapFactory::height()) {
    for (unsigned int i = 0; i < this->width; ++i) {
        std::vector<Cell*> col;
        for (unsigned int j = 0; j < this->height; ++j)
            col.push_back(new Cell());
        this->cells.push_back(col);
    }
}

void Map::set(const std::string& info) {
    //TODO parsear info con Factory y
    // setear objetos y enemigos en mundo de box2d?
}

void Map::tick_enemies_on_cell(Cell* cell) {
    std::vector<Enemy*> enemies = cell->get_enemies();
    std::vector<int> position;

    while (enemies.size() != 0) {
        Projectile* projectile = enemies.front()->tick();

        if (projectile) {
            position = projectile->get_position();
            cells[position[X_COORD_POS]][position[Y_COORD_POS]]
                    ->add(projectile);
        }

        position = enemies.front()->get_position();
        cells[position[X_COORD_POS]][position[Y_COORD_POS]]
                ->add(enemies.front());

        enemies.erase(enemies.begin());
    }
}

void Map::tick_projectiles_on_cell(Cell* cell) {
    std::vector<Projectile*> projectiles = cell->get_projectiles();
    std::vector<int> position;

    while (projectiles.size() != 0) {
        projectiles.front()->tick();

        position = projectiles.front()->get_position();
        cells[position[X_COORD_POS]][position[Y_COORD_POS]]
                ->add(projectiles.front());

        projectiles.erase(projectiles.begin());
    }
}

void Map::tick() {
    for (unsigned int i = 0; i < this->width; ++i)
        for (unsigned int j = 0; j < this->height; ++j) {
            this->tick_enemies_on_cell(cells[i][j]);
            this->tick_projectiles_on_cell(cells[i][j]);
        }
}

void Map::get_rid_of_corpses() {
    for (unsigned int i = 0; i < this->width; ++i)
        for (unsigned int j = 0; j < this->height; ++j)
            this->cells[i][j]->get_rid_of_corpses();
}

Map::~Map() {}
