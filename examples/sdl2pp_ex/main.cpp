#include <iostream>
#include <exception>

#include <SDL2pp/SDL2pp.hh>

int main() {
    try{
        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

