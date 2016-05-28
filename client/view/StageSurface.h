#ifndef MEGAMAN_STAGESCREEN_H
#define MEGAMAN_STAGESCREEN_H

#include <SDL2pp/SDL2pp.hh>
#include <X11/Xlib.h>


class StageSurface {
public:
    explicit StageSurface(::Window window_id);
    void run();
    ~StageSurface();
private:
    SDL2pp::SDL* sdl;
    SDL2pp::Window* window;
    SDL2pp::Renderer* renderer;
    SDL2pp::Texture* sprites;
};


#endif //MEGAMAN_STAGESCREEN_H
