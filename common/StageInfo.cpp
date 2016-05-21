#include <vector>

#include "StageInfo.h"

StageInfo::StageInfo(std::vector<char>& met_positions,
                       std::vector<char>& bumby_positions,
                       std::vector<char>& sniper_positions,
                       std::vector<char>& jumping_sniper_positions,
                       std::vector<char>& block_positions,
                       std::vector<char>& stairs_positions,
                       std::vector<char>& spike_positions,
                     std::vector<char>& cliff_positions) :
        met_positions(met_positions),
        bumby_positions(bumby_positions),
        sniper_positions(sniper_positions),
        jumping_sniper_positions(jumping_sniper_positions),
        block_positions(block_positions),
        stairs_positions(stairs_positions),
        spike_positions(spike_positions),
        cliff_positions(cliff_positions) {}

const std::vector<char> StageInfo::get_met_positions() {
    return this->met_positions;
}

const std::vector<char> StageInfo::get_bumby_positions() {
    return this->bumby_positions;
}

const std::vector<char> StageInfo::get_sniper_positions() {
    return this->sniper_positions;
}

const std::vector<char> StageInfo::get_jumping_sniper_positions() {
    return this->jumping_sniper_positions;
}

const std::vector<char> StageInfo::get_block_positions() {
    return this->block_positions;
}

const std::vector<char> StageInfo::get_stairs_positions() {
    return this->stairs_positions;
}

const std::vector<char> StageInfo::get_spike_positions() {
    return this->spike_positions;
}

const std::vector<char> StageInfo::get_cliff_positions() {
    return this->cliff_positions;
}

StageInfo::~StageInfo() {}
