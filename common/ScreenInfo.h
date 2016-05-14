#ifndef SCREENINFO_H
#define SCREENINFO_H

#include <vector>

class ScreenInfo {
    private:
        const std::vector<char> met_positions;
        const std::vector<char> bumby_positions;
        const std::vector<char> sniper_positions;
        const std::vector<char> jumping_sniper_positions;
        const std::vector<char> block_positions;
        const std::vector<char> stairs_positions;
        const std::vector<char> spike_positions;

    public:
        ScreenInfo(std::vector<char>& met_positions,
                  std::vector<char>& bumby_positions,
                  std::vector<char>& sniper_positions,
                  std::vector<char>& jumping_sniper_positions,
                  std::vector<char>& block_positions,
                  std::vector<char>& stairs_positions,
                  std::vector<char>& spike_positions);
        const std::vector<char> get_met_positions();
        const std::vector<char> get_bumby_positions();
        const std::vector<char> get_sniper_positions();
        const std::vector<char> get_jumping_sniper_positions();
        const std::vector<char> get_block_positions();
        const std::vector<char> get_stairs_positions();
        const std::vector<char> get_spike_positions();
        ~ScreenInfo();
};

#endif //SCREENINFO_H

