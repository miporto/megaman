#include <iostream>
#include <exception>


#include <SDL2pp/SDL2pp.hh>
#include <giomm.h>

#include "StageSurface.h"
#include <X11/Xlib.h>

StageSurface::StageSurface() {
    try {
        sdl = new SDL2pp::SDL(SDL_INIT_VIDEO);
        window = new SDL2pp::Window("Mega Man", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, 640, 480,
                                    SDL_WINDOW_RESIZABLE);
        renderer = new SDL2pp::Renderer(*window, -1, SDL_RENDERER_SOFTWARE);
        sprites = new SDL2pp::Texture(*renderer, "resources/M484SpaceSoldier"
                ".png");
        SDL_Event event;
        while (true) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    return;
                }
            }
            renderer->Clear();
            renderer->Copy(*sprites);
            renderer->Present();
            std::cout << "Check" << std::endl;
            SDL_Delay(5);
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

bool StageSurface::init(::Window window_id) {
    return true;
}

bool StageSurface::run() {
    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return true;
            }
        }
        try {
            renderer->Clear();
            renderer->Copy(*sprites);
            renderer->Present();
            std::cout << "Check" << std::endl;
            SDL_Delay(5000);
            return true;
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
    }
}


StageSurface::~StageSurface() {
    delete sprites;
    delete renderer;
    delete sdl;
}



