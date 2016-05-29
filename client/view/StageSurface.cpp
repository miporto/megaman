#include <iostream>
#include <exception>


#include <SDL2pp/SDL2pp.hh>
#include <giomm.h>

#include "StageSurface.h"
#include "InputHandler.h"
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
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

bool StageSurface::init(::Window window_id) {
    return true;
}

bool StageSurface::run() {
    try {
        bool is_running = false;
        int run_phase = -1; // run animation phase
        double position = 0.0;
        unsigned int prev_ticks = SDL_GetTicks();
//        SDL_Event event;
        while (true) {
            // Timing
            unsigned int frame_ticks = SDL_GetTicks();
            unsigned int frame_delta = frame_ticks - prev_ticks;
            prev_ticks = frame_ticks;
            input_handler.read_input();
            if (input_handler.is_window_closed()) {
                return 0;
            }
//            while (SDL_PollEvent(&event)) {
//                if (event.type == SDL_QUIT) {
//                    return 0;
//                } else if (event.type == SDL_KEYDOWN) {
//                    switch (event.key.keysym.sym) {
//                        case SDLK_RIGHT:
//                            is_running = true;
//                            break;
//                    }
//                } else if (event.type == SDL_KEYUP) {
//                    switch (event.key.keysym.sym) {
//                        case SDLK_RIGHT:
//                            is_running = false;
//                            break;
//                    }
//                }
//            }
            // Update Game state
            if (is_running) {
                position += frame_delta * 0.2;
                run_phase = (frame_ticks / 100) % 8;
            } else {
                run_phase = 0;
            }
            if (position > renderer->GetOutputWidth()) {
                position = -50;
            }
            int vcenter = renderer->GetOutputHeight() / 2;
            // Clear screen
            renderer->Clear();
            int src_x = 8 + 51 * run_phase, src_y = 67;
            renderer->Copy(*sprites,
                           SDL2pp::Rect(src_x, src_y, 50, 50),
                           SDL2pp::Rect((int) position, vcenter - 50, 50, 50));
            renderer->Present();
            SDL_Delay(1);
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

StageSurface::~StageSurface() {
    delete sprites;
    delete renderer;
    delete sdl;
}


