#include "extern/json.hpp"
#include <iostream>
#include <string>
#include <fstream>

using json = nlohmann::json;

int main(){
    std::string file_dump;
    std::string buffer;
    std::ifstream json_file("example.json");
    while (getline(json_file, buffer)) file_dump += buffer;
    json j = json::parse(file_dump);
    std::cout << j["list"][0]["x"] << j["list"][1]["y"] << std::endl;

    return 0;
}
