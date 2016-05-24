#include <vector>

#include "StageInfo.h"

StageInfo::StageInfo(std::vector<Position*>& met_positions,
                       std::vector<Position*>& bumby_positions,
                       std::vector<Position*>& sniper_positions,
                       std::vector<Position*>& jumping_sniper_positions,
                       std::vector<Position*>& block_positions,
                       std::vector<Position*>& stairs_positions,
                       std::vector<Position*>& spike_positions,
                     std::vector<Position*>& cliff_positions) :
        met_positions(met_positions),
        bumby_positions(bumby_positions),
        sniper_positions(sniper_positions),
        jumping_sniper_positions(jumping_sniper_positions),
        block_positions(block_positions),
        stairs_positions(stairs_positions),
        spike_positions(spike_positions),
        cliff_positions(cliff_positions) {}

const std::vector<Position*> StageInfo::clone_vector
        (const std::vector<Position*> v) const {
    std::vector<Position*> clone;
    for (unsigned int i = 0; i < v.size(); ++i)
        clone.push_back(v[i]->clone());
    return clone;
}

const std::vector<Position*> StageInfo::get_met_positions() {
    return this->clone_vector(this->met_positions);
}

const std::vector<Position*> StageInfo::get_bumby_positions() {
    return this->clone_vector(this->bumby_positions);
}

const std::vector<Position*> StageInfo::get_sniper_positions() {
    return this->clone_vector(this->sniper_positions);
}

const std::vector<Position*> StageInfo::get_jumping_sniper_positions() {
    return this->clone_vector(this->jumping_sniper_positions);
}

const std::vector<Position*> StageInfo::get_block_positions() {
    return this->clone_vector(this->block_positions);
}

const std::vector<Position*> StageInfo::get_stairs_positions() {
    return this->clone_vector(this->stairs_positions);
}

const std::vector<Position*> StageInfo::get_spike_positions() {
    return this->clone_vector(this->spike_positions);
}

const std::vector<Position*> StageInfo::get_cliff_positions() {
    return this->clone_vector(this->cliff_positions);
}

StageInfo::~StageInfo() {
    for (unsigned int i = 0; i < this->met_positions.size(); ++i)
        delete this->met_positions[i];
    for (unsigned int i = 0; i < this->bumby_positions.size(); ++i)
        delete this->bumby_positions[i];
    for (unsigned int i = 0; i < this->sniper_positions.size(); ++i)
        delete this->sniper_positions[i];
    for (unsigned int i = 0; i < this->jumping_sniper_positions.size(); ++i)
        delete this->jumping_sniper_positions[i];
    for (unsigned int i = 0; i < this->block_positions.size(); ++i)
        delete this->block_positions[i];
    for (unsigned int i = 0; i < this->stairs_positions.size(); ++i)
        delete this->stairs_positions[i];
    for (unsigned int i = 0; i < this->spike_positions.size(); ++i)
        delete this->spike_positions[i];
    for (unsigned int i = 0; i < this->cliff_positions.size(); ++i)
        delete this->cliff_positions[i];
}
