#ifndef SCREENINFO_H
#define SCREENINFO_H

#include <vector>
#include <common/model/Position.h>

class StageInfo {
    private:
        const std::vector<Position*> met_positions;
        const std::vector<Position*> bumby_positions;
        const std::vector<Position*> sniper_positions;
        const std::vector<Position*> jumping_sniper_positions;
        const std::vector<Position*> block_positions;
        const std::vector<Position*> stairs_positions;
        const std::vector<Position*> spike_positions;
        const std::vector<Position*> cliff_positions;

        const std::vector<Position*> clone_vector
                (const std::vector<Position*> v) const;

    public:
        StageInfo(std::vector<Position*>& met_positions,
                  std::vector<Position*>& bumby_positions,
                  std::vector<Position*>& sniper_positions,
                  std::vector<Position*>& jumping_sniper_positions,
                  std::vector<Position*>& block_positions,
                  std::vector<Position*>& stairs_positions,
                  std::vector<Position*>& spike_positions,
                  std::vector<Position*>& cliff_positions);
        const std::vector<Position*> get_met_positions();
        const std::vector<Position*> get_bumby_positions();
        const std::vector<Position*> get_sniper_positions();
        const std::vector<Position*> get_jumping_sniper_positions();
        const std::vector<Position*> get_block_positions();
        const std::vector<Position*> get_stairs_positions();
        const std::vector<Position*> get_spike_positions();
        const std::vector<Position*> get_cliff_positions();
        ~StageInfo();
};

#endif //SCREENINFO_H

