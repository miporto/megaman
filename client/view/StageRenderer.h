#ifndef MEGAMAN_STAGERENDERER_H
#define MEGAMAN_STAGERENDERER_H

#include <SDL2pp/SDL2pp.hh>

#include "common/StageParser.h"
#include "TileRenderer.h"
#include "ActorRenderer.h"

class TileRenderer;
class StageRenderer {
public:
//    explicit StageRenderer(SDL2pp::Renderer* renderer);
    StageRenderer(SDL2pp::Renderer* renderer,
                  const StageParserInfo& stage_info);
    void render();
    ~StageRenderer();
private:
    void render_stage();
    void render_actors();
    // TODO: stageRenderer should receive the background image in memory
    SDL2pp::Renderer* renderer;
    const StageParserInfo& stage_info;
    SDL2pp::Texture* background;
    TileRenderer tiles;
    ActorRenderer met;
};


#endif //MEGAMAN_STAGERENDERER_H
