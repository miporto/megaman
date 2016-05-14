#include <vector>

#include "ScreenInfo.h"

ScreenInfo::ScreenInfo(std::vector<char>& met_positions,
                       std::vector<char>& bumby_positions,
                       std::vector<char>& sniper_positions,
                       std::vector<char>& jumping_sniper_positions,
                       std::vector<char>& block_positions,
                       std::vector<char>& stairs_positions,
                       std::vector<char>& spike_positions) :
        met_positions(met_positions),
        bumby_positions(bumby_positions),
        sniper_positions(sniper_positions),
        jumping_sniper_positions(jumping_sniper_positions),
        block_positions(block_positions),
        stairs_positions(stairs_positions),
        spike_positions(spike_positions) {}

const std::vector<char> ScreenInfo::get_met_positions() {
    return this->met_positions;
}

const std::vector<char> ScreenInfo::get_bumby_positions() {
    return this->bumby_positions;
}

const std::vector<char> ScreenInfo::get_sniper_positions() {
    return this->sniper_positions;
}

const std::vector<char> ScreenInfo::get_jumping_sniper_positions() {
    return this->jumping_sniper_positions;
}

const std::vector<char> ScreenInfo::get_block_positions() {
    return this->block_positions;
}

const std::vector<char> ScreenInfo::get_stairs_positions() {
    return this->stairs_positions;
}

const std::vector<char> ScreenInfo::get_spike_positions() {
    return this->spike_positions;
}

ScreenInfo::~ScreenInfo() {}
