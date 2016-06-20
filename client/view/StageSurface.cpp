#include <iostream>
#include <exception>
#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>
#include <giomm.h>

#include "client/communication/Client.h"
#include "common/communication/Packet.h"
#include "server/model/GameObjectParser.h"
#include "InputHandler.h"
#include "StageRenderer.h"
#include "StageSurface.h"
#include "Timer.h"

#define SCREEN_FPS 60
#define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS

StageSurface::StageSurface(Client& client) : won_game(false), client(client){
    try {
        std::string s_stage_info = client.receive_stage_info();
        sdl = new SDL2pp::SDL(SDL_INIT_VIDEO);
        window = new SDL2pp::Window("Mega Man", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, 640, 480,
                                    SDL_WINDOW_RESIZABLE);
        window->Maximize();
        renderer = new SDL2pp::Renderer(*window, -1, SDL_RENDERER_SOFTWARE);
        // TODO: stage renderer should receive the stage info in its creation
        stage_renderer = new StageRenderer(renderer, s_stage_info);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

void StageSurface::run() {
    try {
        std::vector<bool> prev_input = input_handler.get_input();
        std::vector<bool> new_input = input_handler.get_input();
        Timer cap_timer;
        while (true) {
            cap_timer.start();
            // Input
            input_handler.read_input();
            new_input = input_handler.get_input();
            if (input_handler.is_window_closed()) {
                return;
            }

            // Update Game state
            send_events(prev_input, new_input);

            // Check if they entered the boss chamber
            if (client.new_chamber_info_packet()) {
                std::string chamber_info = client.receive_chamber_info();
                //std::cout << chamber_info << std::endl;
                stage_renderer->render_boss_chamber(chamber_info);
            }

            // Receive updates
            unsigned int frame_ticks = cap_timer.get_ticks();
            while (client.new_update_packets() &&
                    frame_ticks < SCREEN_TICKS_PER_FRAME * 0.8) {
                UpdatePacket update_packet = client.receive_update();
                stage_renderer->new_update(update_packet.first, update_packet
                        .second);
                frame_ticks = cap_timer.get_ticks();
            }

            // Check for dead actors
            while (client.new_deceased()) {
                stage_renderer->delete_renderer(client.receive_deceased());
            }

            if (stage_renderer->game_ended()) {
                renderer->Clear();
                stage_renderer->render();
                stage_renderer->render_end_game_msg();
                renderer->Present();
                SDL_Delay(1000);
                if (stage_renderer->game_won()) won_game = true;
                return;
            } else {
                renderer->Clear();
                stage_renderer->render();
                renderer->Present();
            }

            prev_input = new_input;
            frame_ticks = cap_timer.get_ticks();
            if (frame_ticks < SCREEN_TICKS_PER_FRAME) {
                //Wait remaining time
                SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
            }
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

bool StageSurface::game_won() {
    return won_game;
}

/*
 * Tells the client to send all the events that happened to the server. For
 * this it checks what keys changed it's status, and send those.
 */
void StageSurface::send_events(std::vector<bool>& prev_input,
                               std::vector<bool>& new_input) {
    for (size_t action_id = 0; action_id < prev_input.size(); ++action_id) {
        if (prev_input[action_id] != new_input[action_id]) {
            std::cout << "Action: " << action_id << " "<< new_input[action_id] <<
                    std::endl;
            client.send_action((char)(action_id), new_input[action_id]);
        }
    }
}

StageSurface::~StageSurface() {
    delete renderer;
    delete sdl;
    delete stage_renderer;
    delete window;
}



