#ifndef MEGAMAN_STAGERENDERER_H
#define MEGAMAN_STAGERENDERER_H

#include <map>
#include <SDL2pp/SDL2pp.hh>
#include <string>
#include <utility>
#include <vector>

#include "common/StageParser.h"
#include "TileRenderer.h"
#include "ActorRenderer.h"

class TileRenderer;
typedef std::pair<int, int> AdjustedPos;

class StageRenderer {
public:
    StageRenderer(SDL2pp::Renderer *renderer, const std::string &stage_info);
    void render();
    void render(const std::string &s_tick_info);
    void update(const std::string &name, const std::string &update_info);
    void delete_renderer(int id);
    ~StageRenderer();

private:
    AdjustedPos adjust_position(float x, float y);
//    void render_stage();
//
//    void render_spawn_actors();
//
//    void render_actors(const std::string &s_tick_info);

    // TODO: stageRenderer should receive the background image in memory
    SDL2pp::Renderer *renderer;
//    StageParserInfo &stage_info;
    SDL2pp::Texture *background;
    std::map<int, TileRendererr*> tile_renderers;
    std::map<int, ActorRendererr*> actor_renderers;
    std::vector<std::string> actors;
    std::vector<std::string> objects;
    TileRendererFactory tile_factory;
    ActorRendererFactory actor_factory;
//    TileRenderers2 tiles_rendererss;
//    TileRenderer tiles;
//    ActorRenderer actors;
};


#endif //MEGAMAN_STAGERENDERER_H
