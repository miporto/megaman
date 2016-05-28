#include <iostream>
#include <exception>


#include <SDL2pp/SDL2pp.hh>
#include <giomm.h>

#include "StageSurface.h"
#include <X11/Xlib.h>

StageSurface::StageSurface() {
    set_title("Stage");
    set_size_request(640, 480);
    set_position(Gtk::WIN_POS_CENTER);
    set_border_width(0);
    Gtk::Socket* socket = manage(new Gtk::Socket);
    add(*socket);
    show_all();
    sigc::slot<bool> slot =  sigc::bind<::Window>(sigc::mem_fun(*this,
    &StageSurface::init), socket->get_id());
    Glib::signal_timeout().connect(slot, 50);
}

bool StageSurface::init(::Window window_id) {
    try {
        sdl = new SDL2pp::SDL(SDL_INIT_VIDEO);
        SDL_Window *s_window = SDL_CreateWindowFrom((void *) window_id);
        if (!s_window) {
            std::cerr << "Couldn't create SDL window: " << SDL_GetError() <<
            std::endl;
            throw std::exception();
        }
        SDL2pp::Window window(s_window);
//        window = new SDL2pp::Window ("Mega Man", SDL_WINDOWPOS_UNDEFINED,
//                              SDL_WINDOWPOS_UNDEFINED, 640, 480,
//                              SDL_WINDOW_RESIZABLE);
        renderer = new SDL2pp::Renderer(window, -1, SDL_RENDERER_SOFTWARE);
        sprites = new SDL2pp::Texture(*renderer, "resources/M484SpaceSoldier"
                ".png");
        sigc::slot<bool> slot = sigc::mem_fun(*this, &StageSurface::run);
        Glib::signal_timeout().connect(slot, 16);
        return false;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return true;
    }
}
bool StageSurface::run() {
//    SDL_Event event;
//    while (true) {
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                return true;
//            }
//        }
//    }
    try {
        renderer->Clear();
        renderer->Copy(*sprites);
        renderer->Present();
        std::cout << "Check" << std::endl;
        //SDL_Delay(5000);
        return true;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}


StageSurface::~StageSurface() {
    delete sprites;
    delete renderer;
    delete sdl;
}



