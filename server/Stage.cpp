#include "Stage.h"

#define MET_ID 1
#define BUMBY_ID 2
#define SNIPER_ID 3
#define JUMPING_SNIPER_ID 4
#define RED_BLOCK_ID 5
#define BLUE_BLOCK_ID 6
#define YELLOW_BLOCK_ID 7
#define STAIRS_ID 8
#define SPIKES_ID 9

StageIDProtected::StageIDProtected() : stage_id(0) {}

void StageIDProtected::set_id(char stage_id) {
    Lock l(this->m);
    this->stage_id = stage_id;
}

char StageIDProtected::operator()() {
    Lock l(this->m);
    return this->stage_id;
}

StageIDProtected::~StageIDProtected() {}

StageFactory::StageFactory(char id) : id(id) {}

std::vector<char> StageFactory::positions_of_spawns(const int screen, const int enemy_id) {
    std::vector<char> positions;

    // uso de variables para que compile
    int i = screen;
    int j = enemy_id;
    i++;
    j++;
    // fin (?)

    //TODO leer .JSON["stage"][this->id][screen]["spawn"][enemy]
    return positions;
}

std::vector<char> StageFactory::positions_of_objects(const int screen, const int object_id) {
    std::vector<char> positions;

    // uso de variables para que compile
    int i = screen;
    int j = object_id;
    i++;
    j++;
    // fin (?)

    //TODO leer .JSON["stage"][this->id][screen]["object"][object]
    return positions;
}

StageFactory::~StageFactory() {}

Stage::Stage(char id, std::vector<Player*>& players) :
    factory(id), players(players), current_screen(0) {}

std::vector<StageInfo*> Stage::next_screen() {
    std::vector<StageInfo*> screen_info;

    // Llenar vector con info de factory
    this->factory.positions_of_spawns(this->current_screen, MET_ID);
    this->factory.positions_of_spawns(this->current_screen, BUMBY_ID);
    this->factory.positions_of_spawns(this->current_screen, SNIPER_ID);
    this->factory.positions_of_spawns(this->current_screen, JUMPING_SNIPER_ID);

    this->factory.positions_of_objects(this->current_screen, RED_BLOCK_ID);
    this->factory.positions_of_objects(this->current_screen, BLUE_BLOCK_ID);
    this->factory.positions_of_objects(this->current_screen, YELLOW_BLOCK_ID);
    this->factory.positions_of_objects(this->current_screen, STAIRS_ID);
    this->factory.positions_of_objects(this->current_screen, SPIKES_ID);

    this->current_screen++;
    return screen_info;
}

Stage::~Stage() {}