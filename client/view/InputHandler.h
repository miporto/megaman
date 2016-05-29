#ifndef MEGAMAN_INPUTHANDLER_H
#define MEGAMAN_INPUTHANDLER_H

#include <SDL2pp/SDL2pp.hh>

class InputHandler {
public:
    InputHandler();
    void read_input();
    bool is_window_closed();
    ~InputHandler();
private:
    SDL_Event event;
    bool window_closed;
};


#endif //MEGAMAN_INPUTHANDLER_H
