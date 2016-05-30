#include "InputHandler.h"
#include "common/communication/Packet.h"

InputHandler::InputHandler() : window_closed(false) { }

void InputHandler::read_input() {
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            window_closed = true;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    keys_held[RIGHT] = true;
                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    keys_held[RIGHT] = false;
                    break;
            }
        }
    }
}

bool* InputHandler::get_input() {
    return keys_held;
}
bool InputHandler::is_window_closed() {
    return window_closed;
}

InputHandler::~InputHandler() { }
