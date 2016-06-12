#include <string>

#include "GameObjectParser.h"
#include "GameObjectSetter.h"
#include "Enemy.h"
#include "Object.h"

GameObjectSetter::GameObjectSetter(const std::string& info,
                                   GameObjectHandler* handler) {
    GameObjectParser parser;
    GameObjectParserInfo positions = parser.stage_info(info);
    this->to_classes(positions, handler);
}

void GameObjectSetter::to_classes(GameObjectParserInfo& positions,
                             GameObjectHandler* handler) {
    typedef GameObjectParserInfo::iterator iterator_info;
    for (iterator_info it = positions.begin(); it != positions.end(); ++it) {
        for (unsigned int i = 0; i < it->second.size(); ++i) {
            if (MET_NAME == it->first) {
                handler->add_game_object(new Met(it->second[i]));
            } else if (BUMBY_NAME == it->first) {
                handler->add_game_object(new Bumby(it->second[i]));
            } else if (SNIPER_NAME == it->first) {
                handler->add_game_object(new Sniper(it->second[i]));
            } else if (JUMPING_SNIPER_NAME == it->first) {
                handler->add_game_object(new JumpingSniper(it->second[i]));
            } else if (BLOCK_NAME == it->first) {
                handler->add_game_object(new Block(it->second[i]));
            } else if (STAIRS_NAME == it->first) {
                handler->add_game_object(new Stairs(it->second[i]));
            } else if (SPIKE_NAME == it->first) {
                handler->add_game_object(new Spike(it->second[i]));
            } else if (CLIFF_NAME == it->first) {
                handler->add_game_object(new Cliff(it->second[i]));
            } else if (DOOR_NAME == it->first) {
                handler->add_game_object(new Door(it->second[i]));
            }
        }
    }
}

GameObjectSetter::~GameObjectSetter() {}
