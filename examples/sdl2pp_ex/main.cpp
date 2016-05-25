#include <iostream>
#include <exception>

#include <SDL2pp/SDL2pp.hh>

int main() {
    try{
        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        SDL2pp::Window window("Mega Man", SDL_WINDOWPOS_UNDEFINED,
                      SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_SOFTWARE);
        SDL2pp::Texture sprites(renderer, "resources/M484SpaceSoldier.png");

        // Game state
        bool is_running = false;
        int run_phase = -1; // run animation phase
        double position = 0.0;
        unsigned int prev_ticks = SDL_GetTicks();

        while (true) {
            // Timing
            unsigned int frame_ticks = SDL_GetTicks();
            unsigned int frame_delta = frame_ticks - prev_ticks;
            prev_ticks = frame_ticks;

            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    return 0;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_RIGHT:
                            is_running = true;
                            break;
                    }
                } else if (event.type == SDL_KEYUP) {
                    switch (event.key.keysym.sym) {
                        case SDLK_RIGHT:
                            is_running = false;
                            break;
                    }
                }
            }

            // Update Game state
            if (is_running) {
                position += frame_delta * 0.2;
                run_phase = (frame_ticks/100) % 8;
            } else {
                run_phase = 0;
            }

            if (position > renderer.GetOutputWidth()) {
                position = -50;
            }
            int vcenter = renderer.GetOutputHeight() / 2;

            // Clear screen
            renderer.Clear();

            int src_x = 8 + 51 * run_phase, src_y = 67;
            renderer.Copy(sprites,
                          SDL2pp::Rect(src_x, src_y, 50, 50),
                          SDL2pp::Rect((int) position, vcenter - 50, 50, 50));
            renderer.Present();
            SDL_Delay(1);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

