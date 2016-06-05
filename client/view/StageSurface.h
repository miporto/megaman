#ifndef MEGAMAN_STAGESCREEN_H
#define MEGAMAN_STAGESCREEN_H

#include <SDL2pp/SDL2pp.hh>
#include <string>
#include <vector>

#include "client/communication/Client.h"
#include "common/StageParser.h"
#include "InputHandler.h"
#include "MegamanRenderer.h"
#include "StageRenderer.h"

class StageSurface {
public:
    explicit StageSurface(Client& client);
    void run();
    ~StageSurface();
private:
    void send_events(std::vector<bool>& prev_input,
                     std::vector<bool>& new_input);
    // TODO: move this method to a more appropiate class
    void replace_substr(std::string& input, const std::string& old_str, const
    std::string& new_str);
    Client& client;
    StageParserInfo stage_info;
    SDL2pp::SDL* sdl;
    SDL2pp::Window* window;
    SDL2pp::Renderer* renderer;
    SDL2pp::Texture* sprites;
    InputHandler input_handler;
    StageRenderer* stage_renderer;
    MegamanRenderer* megaman_renderer;
};


#endif //MEGAMAN_STAGESCREEN_H
