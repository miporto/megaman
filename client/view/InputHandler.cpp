#include <iostream>
#include <string>
#include <vector>

#include "InputHandler.h"
#include "common/communication/Packet.h"

InputHandler::InputHandler() : window_closed(false), keys_held(11) {
    for (size_t i = 0; i < keys_held.size(); ++i) {
        keys_held[i] = false;
    }
}

void InputHandler::read_input() {
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            window_closed = true;
        } else if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    keys_held[LEFT-1] = true;
                    break;
                case SDLK_UP:
                    keys_held[UP-1] = true;
                    break;
                case SDLK_RIGHT:
                    keys_held[RIGHT-1] = true;
                    break;
                case SDLK_DOWN:
                    keys_held[DOWN-1] = true;
                    break;
                case SDLK_1:
                    keys_held[AMMO_0-1] = true;
                    break;
                case SDLK_2:
                    keys_held[AMMO_1-1] = true;
                    break;
                case SDLK_3:
                    keys_held[AMMO_2-1] = true;
                    break;
                case SDLK_4:
                    keys_held[AMMO_3-1] = true;
                    break;
                case SDLK_5:
                    keys_held[AMMO_4-1] = true;
                    break;
                case SDLK_6:
                    keys_held[AMMO_5-1] = true;
                    break;
                case SDLK_s:
                    keys_held[SHOOT-1] = true;
                    break;
            }
        } else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    keys_held[LEFT-1] = false;
                    break;
                case SDLK_UP:
                    keys_held[UP-1] = false;
                    break;
                case SDLK_RIGHT:
                    keys_held[RIGHT-1] = false;
                    break;
                case SDLK_DOWN:
                    keys_held[DOWN-1] = false;
                    break;
                case SDLK_0:
                    keys_held[AMMO_0-1] = false;
                    break;
                case SDLK_1:
                    keys_held[AMMO_1-1] = false;
                    break;
                case SDLK_2:
                    keys_held[AMMO_2-1] = false;
                    break;
                case SDLK_3:
                    keys_held[AMMO_3-1] = false;
                    break;
                case SDLK_4:
                    keys_held[AMMO_4-1] = false;
                    break;
                case SDLK_5:
                    keys_held[AMMO_5-1] = false;
                    break;
                case SDLK_s:
                    keys_held[SHOOT-1] = false;
                    break;
            }
        }
    }
}

std::vector<bool> InputHandler::get_input() {
    return keys_held;
}
bool InputHandler::is_window_closed() {
    return window_closed;
}

InputHandler::~InputHandler() { }
