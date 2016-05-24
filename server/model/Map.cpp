#include <vector>
#include <utility>

#include "common/communication/StageInfo.h"
#include "Map.h"

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

Map::Map() {
    for (unsigned int i = 0; i < WIDTH; ++i) {
        std::vector<Cell*> col;
        for (unsigned int j = 0; j < HEIGHT; ++j)
            col.push_back(new Cell());
        this->cells.push_back(col);
    }
}

void Map::set(StageInfo* info) {
    std::vector<Position*> positions;
    std::pair<int, int> position;

    // Completa vector objects de las celdas
    positions = info->get_block_positions();
    for (unsigned int i = 0; i < positions.size(); ++i) {
        position = positions[i]->get_position();
        this->cells[position.first][position.second]->add
                (new Block(position.first, position.second));
        delete positions[i];
    }
    positions = info->get_stairs_positions();
    for (unsigned int i = 0; i < positions.size(); ++i) {
        position = positions[i]->get_position();
        this->cells[position.first][position.second]->add
                (new Stairs(position.first, position.second));
        delete positions[i];
    }
    positions = info->get_spike_positions();
    for (unsigned int i = 0; i < positions.size(); ++i) {
        position = positions[i]->get_position();
        this->cells[position.first][position.second]->add
                (new Spike(position.first, position.second));
        delete positions[i];
    }
    positions = info->get_cliff_positions();
    for (unsigned int i = 0; i < positions.size(); ++i) {
        position = positions[i]->get_position();
        this->cells[position.first][position.second]->add
                (new Cliff(position.first, position.second));
        delete positions[i];
    }

    // Completa vector enemies de las celdas
    positions = info->get_met_positions();
    for (unsigned int i = 0; i < positions.size(); ++i) {
        position = positions[i]->get_position();
        this->cells[position.first][position.second]->add
                (new Met(position.first, position.second));
        delete positions[i];
    }
    positions = info->get_bumby_positions();
    for (unsigned int i = 0; i < positions.size(); ++i) {
        position = positions[i]->get_position();
        this->cells[position.first][position.second]->add
                (new Bumby(position.first, position.second));
        delete positions[i];
    }
    positions = info->get_sniper_positions();
    for (unsigned int i = 0; i < positions.size(); ++i) {
        position = positions[i]->get_position();
        this->cells[position.first][position.second]->add
                (new Sniper(position.first, position.second));
        delete positions[i];
    }
    positions = info->get_jumping_sniper_positions();
    for (unsigned int i = 0; i < positions.size(); ++i) {
        position = positions[i]->get_position();
        this->cells[position.first][position.second]->add
                (new JumpingSniper(position.first, position.second));
        delete positions[i];
    }
}

void Map::tick_enemies_on_cell(Cell* cell) {
    std::vector<Enemy*> enemies = cell->get_enemies();
    std::pair<int, int> position;

    while (enemies.size() != 0) {
        Projectile* projectile = enemies.front()->tick();

        if (projectile) {
            position = projectile->get_position();
            cells[position.first][position.second]->add(projectile);
        }

        position = enemies.front()->get_position();
        cells[position.first][position.second]->add(enemies.front());

        enemies.erase(enemies.begin());
    }
}

void Map::tick_projectiles_on_cell(Cell* cell) {
    std::vector<Projectile*> projectiles = cell->get_projectiles();
    std::pair<int, int> position;

    while (projectiles.size() != 0) {
        projectiles.front()->tick();

        position = projectiles.front()->get_position();
        cells[position.first][position.second]->add(projectiles.front());

        projectiles.erase(projectiles.begin());
    }
}

void Map::tick() {
    for (unsigned int i = 0; i < WIDTH; ++i)
        for (unsigned int j = 0; j < HEIGHT; ++j) {
            this->tick_enemies_on_cell(cells[i][j]);
            this->tick_projectiles_on_cell(cells[i][j]);
        }
}

void Map::get_rid_of_corpses() {
    for (unsigned int i = 0; i < WIDTH; ++i)
        for (unsigned int j = 0; j < HEIGHT; ++j)
            this->cells[i][j]->get_rid_of_corpses();
}

Map::~Map() {}
