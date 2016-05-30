#include <iostream>
#include <exception>


#include <SDL2pp/SDL2pp.hh>
#include <giomm.h>

#include "common/communication/Packet.h"
#include "InputHandler.h"
#include "StageRenderer.h"
#include "StageSurface.h"

// TODO: relate with the client to communicate with the server
StageSurface::StageSurface() {
    try {
        sdl = new SDL2pp::SDL(SDL_INIT_VIDEO);
        window = new SDL2pp::Window("Mega Man", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, 640, 480,
                                    SDL_WINDOW_RESIZABLE);
        renderer = new SDL2pp::Renderer(*window, -1, SDL_RENDERER_SOFTWARE);
        sprites = new SDL2pp::Texture(*renderer, "resources/M484SpaceSoldier"
                ".png");
        stageRenderer = new StageRenderer(renderer);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

void StageSurface::run() {
    try {
        int run_phase = -1; // run animation phase
        double position = 0.0;
        unsigned int prev_ticks = SDL_GetTicks();
//        bool* prev_input;
        bool* new_input;
        while (true) {
            // Timing
            unsigned int frame_ticks = SDL_GetTicks();
            unsigned int frame_delta = frame_ticks - prev_ticks;
            prev_ticks = frame_ticks;

            // Input
//            prev_input  = input_handler.get_input();
            input_handler.read_input();
            new_input  = input_handler.get_input();
            if (input_handler.is_window_closed()) {
                // TODO: send sht_dwn signal to server
                return;
            }
            // Update Game state
//            send_events(prev_input, new_input);
            if (new_input[RIGHT]) {
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
            stageRenderer->render();
            int src_x = 8 + 51 * run_phase, src_y = 67;
            renderer->Copy(*sprites,
                           SDL2pp::Rect(src_x, src_y, 50, 50),
                           SDL2pp::Rect((int) position, vcenter - 50, 50, 50));
            renderer->Present();
            SDL_Delay(1);
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

/*
 * Tells the client to send all the events that happened to the server. For
 * this it checks what keys changed it's status, and send those.
 */
void StageSurface::send_events(bool* prev_input, bool* new_input) {
    for (size_t i = 0; i < sizeof(*prev_input) / sizeof(prev_input[0]); ++i) {
        if (prev_input[i] != new_input[i]) {
            // TODO: Call client method to send the event
            continue;
        }
    }
}
StageSurface::~StageSurface() {
    delete sprites;
    delete renderer;
    delete sdl;
    delete stageRenderer;
}



