#ifndef MEGAMAN_STAGESCREEN_H
#define MEGAMAN_STAGESCREEN_H

#include <SDL2pp/SDL2pp.hh>
#include <gtkmm/window.h>
#include <gtkmm/socket.h>

#include "InputHandler.h"

class StageSurface {
public:
    StageSurface();
    bool init(::Window window_id);
    bool run();
    ~StageSurface();
private:
    SDL2pp::SDL* sdl;
    SDL2pp::Window* window;
    SDL2pp::Renderer* renderer;
    SDL2pp::Texture* sprites;
    InputHandler input_handler;
};


#endif //MEGAMAN_STAGESCREEN_H