#ifndef MEGAMAN_STAGESCREEN_H
#define MEGAMAN_STAGESCREEN_H

#include <SDL2pp/SDL2pp.hh>
#include <gtkmm/window.h>
#include <gtkmm/socket.h>
#include <vector>

#include "client/communication/Client.h"
#include "InputHandler.h"
#include "MegamanRenderer.h"
#include "StageRenderer.h"

class StageSurface {
public:
//    StageSurface();
    explicit StageSurface(Client& client);
    void run();
    ~StageSurface();
private:
    Client& client;
    void send_events(std::vector<bool>& prev_input,
                     std::vector<bool>& new_input);
    SDL2pp::SDL* sdl;
    SDL2pp::Window* window;
    SDL2pp::Renderer* renderer;
    SDL2pp::Texture* sprites;
    InputHandler input_handler;
    StageRenderer* stage_renderer;
    MegamanRenderer* megaman_renderer;
};


#endif //MEGAMAN_STAGESCREEN_H
