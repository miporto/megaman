#ifndef MEGAMAN_INPUTHANDLER_H
#define MEGAMAN_INPUTHANDLER_H

#include <SDL2pp/SDL2pp.hh>
#include <vector>

class InputHandler {
public:
    InputHandler();
    void read_input();
    std::vector<bool> get_input();
    bool is_window_closed();
    ~InputHandler();
private:
    SDL_Event event;
    bool window_closed;
    std::vector<bool> keys_held;//bool keys_held[5] = {false};
};


#endif //MEGAMAN_INPUTHANDLER_H

