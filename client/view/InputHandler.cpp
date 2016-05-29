#include "InputHandler.h"

InputHandler::InputHandler() : window_closed(false) {}

void InputHandler::read_input() {
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            window_closed = true;
        }
    }
}
bool InputHandler::is_window_closed() {
    return window_closed;
}

InputHandler::~InputHandler() {}
