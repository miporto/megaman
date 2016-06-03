#ifndef MEGAMAN_STAGERENDERER_H
#define MEGAMAN_STAGERENDERER_H

#include <SDL2pp/SDL2pp.hh>

#include "common/StageParser.h"

class StageRenderer {
public:
    explicit StageRenderer(SDL2pp::Renderer* renderer);
//    StageRenderer(SDL2pp::Renderer* renderer, StageParserInfo& stage_info);
    void render();
    ~StageRenderer();
private:
    // TODO: stageRenderer should receive the background image in memory
    SDL2pp::Renderer* renderer;
//    StageParserInfo& stage_info;
    SDL2pp::Texture* background;
};


#endif //MEGAMAN_STAGERENDERER_H
