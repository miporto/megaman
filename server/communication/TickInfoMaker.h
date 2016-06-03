#ifndef TICKINFOMAKER_H
#define TICKINFOMAKER_H

#include <vector>
#include <string>

#include "extern/libjson/json.hpp"

using json = nlohmann::json;

class TickInfoMaker {
    private:
        json info;
    public:
        void add(const std::string& name, const std::string& obj_info);
        /*
        void add_player(const std::string& name,
                        std::vector<int> pos, int energy);
        void add_enemy(const std::string& name,
                       std::vector<int> pos);
        void add_projectile(const std::string& name,
                            std::vector<int> pos);
        */
        const std::string str();
        ~TickInfoMaker();
};

#endif //TICKINFOMAKER_H
