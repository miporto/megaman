#ifndef MEGAMAN_STAGERENDERER_H
#define MEGAMAN_STAGERENDERER_H

#include <SDL2pp/SDL2pp.hh>

#include "common/StageParser.h"
#include "BlockRenderer.h"
#include "MetRenderer.h"

class BlockRenderer;
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
    BlockRenderer block;
    MetRenderer met;
};


#endif //MEGAMAN_STAGERENDERER_H
