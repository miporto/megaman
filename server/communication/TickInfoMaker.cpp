#include <vector>
#include <string>

#include "TickInfoMaker.h"

void TickInfoMaker::add(const std::string& name, const std::string& obj_info) {
    this->info[name] += obj_info;
}

const std::string TickInfoMaker::str() { return this->info.dump(); }

TickInfoMaker::~TickInfoMaker() {}
