#include <string>
#include "ActorRenderer.h"
#include "Camera.h"

ActorRendererr::ActorRendererr(SDL2pp::Renderer *renderer,
                               SDL2pp::Texture *sprites, Camera &camera,
                               float pos_x, float pos_y) : renderer(renderer),
                                                           sprites(sprites),
                                                           camera(camera),
                                                           pos_x(pos_x),
                                                           pos_y(pos_y),
                                                           dir_x(0), dir_y(0) {}

void ActorRendererr::update(float pos_x, float pos_y, int dir_x, int
dir_y) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->dir_x = dir_x;
    this->dir_y = dir_y;
}

float ActorRendererr::get_x() {
    return pos_x;
}

float ActorRendererr::get_y(){
    return pos_y;
}

void MetRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    renderer->Copy(*sprites,
                   SDL2pp::Rect(57, 17, 18, 19),
                   SDL2pp::Rect(pos.first, pos.second, 50, 50));
}

void MegaManRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    renderer->Copy(*sprites, SDL2pp::Rect(103, 10, 32, 28),
                   SDL2pp::Rect(pos.first , pos.second, 50, 50));
}

ActorRendererFactory::ActorRendererFactory(SDL2pp::Renderer *renderer,
                                           Camera &camera) : renderer(renderer),
                                                             camera(camera){
    sprites = new SDL2pp::Texture(*renderer, "resources/mm3_enemysheet.png");
    meg_sprites = new SDL2pp::Texture(*renderer, "resources/8bitmegaman"
            ".png");
    actor_renderers["Met"] = MET_R;
    actor_renderers["MegaMan"] = MEGAMAN_R;
}

ActorRendererr *ActorRendererFactory::build_actor_renderer(std::string
                                                           tile_type,
                                                           float pos_x,
                                                           float pos_y) {
    ActorRendererr *actor_renderer = NULL;
    ActorRendererType tile_renderer_id = actor_renderers[tile_type];
    switch (tile_renderer_id) {
        case MET_R:
            actor_renderer = new MetRenderer(renderer, sprites, camera, pos_x,
            pos_y);
            break;
        case MEGAMAN_R:
            actor_renderer = new MegaManRenderer(renderer, meg_sprites, camera,
            pos_x, pos_y);
            break;
        default:
            throw "ERROR: Non-existint actor renderer!";
    }
    return actor_renderer;
}
