#include "extern/libjson/json.hpp"
#include <iostream>
#include <string>
#include <fstream>

using json = nlohmann::json;

int main(){
//    std::string file_dump;
//    std::string buffer;
//    std::ifstream json_file("example.json");
//    while (getline(json_file, buffer)) file_dump += buffer;
//    json j = json::parse(file_dump);
//    std::cout << j["list"][0]["x"] << j["list"][1]["y"] << std::endl;

    std::string test = "{\"object\":{\"Block\":[{\"x\":10,\"y\": \"11.7\"}]}}";
    json j = json::parse(test);
    std::cout << j.dump() << std::endl;
    std::string s_a = j["object"]["Block"][0]["y"];
    float a = stof(s_a);
    std::cout << a << std::endl;
    std::string s_b = "13.456";
    float b = stof(s_b);
    std::cout << b << std::endl;
    return 0;
}
