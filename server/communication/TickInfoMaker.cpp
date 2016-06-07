#include <vector>
#include <string>

#include "TickInfoMaker.h"

//#define X_COORD_POS 0
//#define Y_COORD_POS 1
//#define DIRECTION_X_POS 2
//#define DIRECTION_Y_POS 3

void TickInfoMaker::add(const std::string& name, const std::string& obj_info) {
    if (obj_info == "") return;
    this->info[name] += obj_info;
}

const std::string TickInfoMaker::str() { return this->info.dump(); }

TickInfoMaker::~TickInfoMaker() {}
