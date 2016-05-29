#include "InputHandler.h"

InputHandler::InputHandler() : window_closed(false) { }

void InputHandler::read_input() {
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            window_closed = true;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    // set right to false
                    break;
            }

        }
    }
}

bool InputHandler::is_window_closed() {
    return window_closed;
}

InputHandler::~InputHandler() { }
