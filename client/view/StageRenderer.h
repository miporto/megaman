#ifndef MEGAMAN_STAGERENDERER_H
#define MEGAMAN_STAGERENDERER_H

#include <map>
#include <SDL2pp/SDL2pp.hh>
#include <string>
#include <vector>

#include "common/StageParser.h"
#include "TileRenderer.h"
#include "ActorRenderer.h"
#include "Camera.h"

class TileRenderer;

class StageRenderer {
public:
    StageRenderer(SDL2pp::Renderer *renderer, const std::string &stage_info);
    void render();
    void update(const std::string &name, const std::string &update_info);
    void delete_renderer(int id);
    ~StageRenderer();

private:
    // TODO: stageRenderer should receive the background image in memory
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *background;
    Camera camera;
    std::map<int, TileRenderer*> tile_renderers;
    std::map<int, ActorRenderer*> actor_renderers;
    std::vector<std::string> actors;
    std::vector<std::string> objects;
    TileRendererFactory tile_factory;
    ActorRendererFactory actor_factory;
};


#endif //MEGAMAN_STAGERENDERER_H
