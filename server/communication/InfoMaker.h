#ifndef TICKINFOMAKER_H
#define TICKINFOMAKER_H

#include <vector>
#include <string>

#include "extern/libjson/json.hpp"

using json = nlohmann::json;

class InfoMaker {
    private:
        json info;
    public:
        void add(const std::string& name, const std::string& obj_info);
        const std::string str();
        ~InfoMaker();
};

#endif //TICKINFOMAKER_H
