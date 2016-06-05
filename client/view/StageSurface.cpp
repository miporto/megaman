#include <iostream>
#include <exception>
#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>
#include <giomm.h>

#include "client/communication/Client.h"
#include "common/communication/Packet.h"
#include "common/StageParser.h"
#include "InputHandler.h"
#include "MegamanRenderer.h"
#include "StageRenderer.h"
#include "StageSurface.h"

void StageSurface::replace_substr(std::string& input,
                                  const std::string& old_str,
                                  const std::string &new_str) {
    size_t index = 0;
    while ( (index = input.find(old_str, index))!= std::string::npos ) {
        input.replace(index, old_str.size(), new_str);
        index += new_str.size();
    }
}

StageSurface::StageSurface(Client& client) : client(client){
    try {
        std::string s_stage_info = client.receive_stage_info();
        replace_substr(s_stage_info, ",", " ,");
//        s_stage_info = "{\"object\":{\"Block\":[{\"x\":10 ,\"y\":11}]}}";
        StageParser stage_parser;
        stage_info = stage_parser.stage_info(s_stage_info);
        sdl = new SDL2pp::SDL(SDL_INIT_VIDEO);
        window = new SDL2pp::Window("Mega Man", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, 640, 480,
                                    SDL_WINDOW_RESIZABLE);
        renderer = new SDL2pp::Renderer(*window, -1, SDL_RENDERER_SOFTWARE);
        sprites = new SDL2pp::Texture(*renderer, "resources/M484SpaceSoldier"
                ".png");
        // TODO: stage renderer should receive the stage info in its creation
        stage_renderer = new StageRenderer(renderer, stage_info);
        megaman_renderer = new MegamanRenderer(renderer);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

void StageSurface::run() {
    try {
//        int run_phase = -1; // run animation phase
        double position = 0.0;
        unsigned int prev_ticks = SDL_GetTicks();
        std::vector<bool> prev_input = input_handler.get_input();
        std::vector<bool> new_input = input_handler.get_input();
        while (true) {
            // Timing
            unsigned int frame_ticks = SDL_GetTicks();
            unsigned int frame_delta = frame_ticks - prev_ticks;
            prev_ticks = frame_ticks;

            // Input
            input_handler.read_input();
            new_input = input_handler.get_input();
            if (input_handler.is_window_closed()) {
                // TODO: send sht_dwn signal to server
                return;
            }
            // Update Game state
            send_events(prev_input, new_input);
            if (new_input[RIGHT]) {
                position += frame_delta * 0.2;
//                run_phase = (frame_ticks / 100) % 8;
            }
//            } else {
//                run_phase = 0;
//            }
            // Receive tick info
            std::string s_tick_info = client.receive_stage_info();
            replace_substr(s_tick_info, ",", " ,");
            if (position > renderer->GetOutputWidth()) {
                position = -50;
            }
            int vcenter = renderer->GetOutputHeight() - 50;
            // Clear screen
            renderer->Clear();
            stage_renderer->render(s_tick_info);
//            int src_x = 8 + 51 * run_phase, src_y = 67;
            megaman_renderer->render((int) position, vcenter);
            renderer->Present();
            SDL_Delay(1);
            prev_input = new_input;
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
void StageSurface::send_events(std::vector<bool>& prev_input,
                               std::vector<bool>& new_input) {
    for (size_t action_id = 0; action_id < prev_input.size(); ++action_id) {
        if (prev_input[action_id] != new_input[action_id]) {
            client.send_action((char)action_id, new_input[action_id]);
        }
    }
}

StageSurface::~StageSurface() {
    delete sprites;
    delete renderer;
    delete sdl;
    delete stage_renderer;
    delete megaman_renderer;
}



