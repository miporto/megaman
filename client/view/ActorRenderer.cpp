#include <string>
#include "ActorRenderer.h"
#include "Camera.h"

ActorRenderer::ActorRenderer(SDL2pp::Renderer *renderer,
                               SDL2pp::Texture *sprites, Camera &camera,
                               float pos_x, float pos_y) : renderer(renderer),
                                                           sprites(sprites),
                                                           camera(camera),
                                                           pos_x(pos_x),
                                                           pos_y(pos_y),
                                                           dir_x(0), dir_y(0) {}

void ActorRenderer::update(float pos_x, float pos_y, int dir_x, int
dir_y) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->dir_x = dir_x;
    this->dir_y = dir_y;
}

float ActorRenderer::get_x() {
    return pos_x;
}

float ActorRenderer::get_y(){
    return pos_y;
}

void MetRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites,
                   SDL2pp::Rect(57, 17, 18, 19),
                   SDL2pp::Rect(pos.first, pos.second, size, size));
}

void MegaManRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites, SDL2pp::Rect(103, 10, 32, 28),
                   SDL2pp::Rect(pos.first , pos.second, size, size));
}

void BombManRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites, SDL2pp::Rect(3, 9, 24, 24),
                   SDL2pp::Rect(pos.first , pos.second, size, size));
}

ActorRendererFactory::ActorRendererFactory(SDL2pp::Renderer *renderer,
                                           Camera &camera) : renderer(renderer),
                                                             camera(camera){
    meg_sprites = new SDL2pp::Texture(*renderer, "resources/8bitmegaman.png");
    enemy_sprites = new SDL2pp::Texture(*renderer, "resources/mm3_enemysheet."
            "png");
    bomb_man_sprites = new SDL2pp::Texture(*renderer, "resources/bomb_man.png");
    actor_renderers["Met"] = MET_R;
    actor_renderers["MegaMan"] = MEGAMAN_R;
    actor_renderers["BombMan"] = BOMBMAN_R;
}

ActorRenderer *ActorRendererFactory::build_actor_renderer(std::string
                                                           tile_type,
                                                           float pos_x,
                                                           float pos_y) {
    ActorRenderer *actor_renderer = NULL;
    ActorRendererType tile_renderer_id = actor_renderers[tile_type];
    switch (tile_renderer_id) {
        case MET_R:
            actor_renderer = new MetRenderer(renderer, enemy_sprites, camera,
                                             pos_x, pos_y);
            break;
        case MEGAMAN_R:
            actor_renderer = new MegaManRenderer(renderer, meg_sprites, camera,
            pos_x, pos_y);
            break;
        case BOMBMAN_R:
            actor_renderer = new BombManRenderer(renderer, bomb_man_sprites,
                                                 camera, pos_x, pos_y);
            break;
        default:
            throw "ERROR: Non-existint actor renderer!";
    }
    return actor_renderer;
}
