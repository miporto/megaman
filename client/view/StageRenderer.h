#ifndef MEGAMAN_STAGERENDERER_H
#define MEGAMAN_STAGERENDERER_H

#include <SDL2pp/SDL2pp.hh>
#include <string>

#include "common/StageParser.h"
#include "TileRenderer.h"
#include "ActorRenderer.h"

class TileRenderer;

class StageRenderer {
public:
    StageRenderer(SDL2pp::Renderer *renderer, StageParserInfo &stage_info);

    void render(const std::string &s_tick_info);

    void update(const std::string &info);

    void delete_renderer(int id);

    ~StageRenderer();

private:
    void render_stage();

    void render_spawn_actors();

    void render_actors(const std::string &s_tick_info);

    // TODO: stageRenderer should receive the background image in memory
    SDL2pp::Renderer *renderer;
    StageParserInfo &stage_info;
    SDL2pp::Texture *background;
    TileRenderers2 tiles_rendererss;
    TileRenderer tiles;
    ActorRenderer actors;
};


#endif //MEGAMAN_STAGERENDERER_H
