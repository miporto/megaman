#include <string>
#include <vector>

#include "InputHandler.h"
#include "common/communication/Packet.h"

InputHandler::InputHandler() : window_closed(false), keys_held(5) {
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
                    keys_held[LEFT] = true;
                    break;
                case SDLK_UP:
                    keys_held[UP] = true;
                    break;
                case SDLK_RIGHT:
                    keys_held[RIGHT] = true;
                    break;
                case SDLK_s:
                    keys_held[SHOOT] = true;
                    break;
            }
        } else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    keys_held[LEFT] = false;
                    break;
                case SDLK_UP:
                    keys_held[UP] = false;
                    break;
                case SDLK_RIGHT:
                    keys_held[RIGHT] = false;
                    break;
                case SDLK_s:
                    keys_held[SHOOT] = true;
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
