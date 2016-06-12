#include <vector>
#include <string>

#include "InfoMaker.h"

void InfoMaker::add(const std::string& name, const std::string& obj_info) {
    this->info[name] += obj_info;
}

const std::string InfoMaker::str() { return this->info.dump(); }

InfoMaker::~InfoMaker() {}
