#ifndef MEGAMAN_STAGESCREEN_H
#define MEGAMAN_STAGESCREEN_H

#include <SDL2pp/SDL2pp.hh>
#include <gtkmm/window.h>
#include <gtkmm/socket.h>

#include "InputHandler.h"
#include "StageRenderer.h"

class StageSurface {
public:
    StageSurface();
    void run();
    ~StageSurface();
private:
    void send_events(bool* prev_input, bool* new_input);
    SDL2pp::SDL* sdl;
    SDL2pp::Window* window;
    SDL2pp::Renderer* renderer;
    SDL2pp::Texture* sprites;
    InputHandler input_handler;
    StageRenderer* stageRenderer;
};


#endif //MEGAMAN_STAGESCREEN_H
