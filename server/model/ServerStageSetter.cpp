#include <string>

#include "common/StageParser.h"
#include "ServerStageSetter.h"
#include "Map.h"

ServerStageSetter::ServerStageSetter(const std::string& info, Map* map) {
    StageParser parser;
    StageParserInfo positions = parser.stage_info(info);
    this->to_classes(positions, map);
}

void ServerStageSetter::to_classes(StageParserInfo& positions, Map* map) {
    typedef StageParserInfo::iterator iterator_info;
    for (iterator_info it = positions.begin(); it != positions.end(); ++it) {
        for (unsigned int i = 0; i < it->second.size(); ++i) {
            if (MET_NAME == it->first) {
                map->add_enemy(new Met(it->second[i]));
            } else if (BUMBY_NAME == it->first) {
                map->add_enemy(new Bumby(it->second[i]));
            } else if (SNIPER_NAME == it->first) {
                map->add_enemy(new Sniper(it->second[i]));
            } else if (JUMPING_SNIPER_NAME == it->first) {
                map->add_enemy(new JumpingSniper(it->second[i]));
            } else if (BLOCK_NAME == it->first) {
                map->add_object(new Block(it->second[i]));
            } else if (STAIRS_NAME == it->first) {
                map->add_object(new Stairs(it->second[i]));
            } else if (SPIKE_NAME == it->first) {
                map->add_object(new Spike(it->second[i]));
            } else if (CLIFF_NAME == it->first) {
                map->add_object(new Cliff(it->second[i]));
            }
        }
    }
}

ServerStageSetter::~ServerStageSetter() {}
