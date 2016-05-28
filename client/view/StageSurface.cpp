#include <iostream>
#include <exception>

#include <SDL2pp/SDL2pp.hh>

#include "StageSurface.h"

StageSurface::StageSurface() {
    set_title("Stage");
    set_size_request(640, 480);
    set_position(Gtk::WIN_POS_CENTER);
    set_border_width(0);
    add(socket);

    try {
        sdl = new SDL2pp::SDL(SDL_INIT_VIDEO);
        SDL_Window *s_window = SDL_CreateWindowFrom((void *) socket.get_id());
        if (!s_window) {
            std::cerr << "Couldn't create SDL window: " << SDL_GetError() <<
            std::endl;
            return;
        }
        window = new SDL2pp::Window(s_window);
//        window = new SDL2pp::Window ("Mega Man", SDL_WINDOWPOS_UNDEFINED,
//                              SDL_WINDOWPOS_UNDEFINED, 640, 480,
//                              SDL_WINDOW_RESIZABLE);
        renderer = new SDL2pp::Renderer(*window, -1, SDL_RENDERER_SOFTWARE);
        sprites = new SDL2pp::Texture(*renderer, "resources/M484SpaceSoldier"
                ".png");
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
    show_all();
}

void StageSurface::run() {
//    SDL_Event event;
//    while (true) {
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                return;
//            }
//        }
//        renderer->Clear();
//        renderer->Copy(*sprites);
//        renderer->Present();
//        SDL_Delay(5000);
//    }
}

StageSurface::~StageSurface() { }



