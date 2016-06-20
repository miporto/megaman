#include <string>
#include "ActorRenderer.h"
#include "Camera.h"

ActorRenderer::ActorRenderer(SDL2pp::Renderer *renderer,
                               SDL2pp::Texture *sprites, Camera &camera,
                               float pos_x, float pos_y) : renderer(renderer),
                                                           sprites(sprites),
                                                           camera(camera),
                                                           pos_x(pos_x),
                                                           pos_y(pos_y), covered(0){}

void ActorRenderer::update(float pos_x, float pos_y, char covered) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->covered = covered;
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
    if (covered != 0) {
        renderer->Copy(*sprites,
                       SDL2pp::Rect(35, 21, 18, 15),
                       SDL2pp::Rect(pos.first, pos.second, size, size));
    } else {
        renderer->Copy(*sprites,
                       SDL2pp::Rect(57, 17, 18, 19),
                       SDL2pp::Rect(pos.first, pos.second, size, size));
    }
}

void BumbyRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites,
                   SDL2pp::Rect(378, 385, 16, 22),
                   SDL2pp::Rect(pos.first, pos.second, size, size));
}

void SniperRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites,
                   SDL2pp::Rect(318, 241, 25, 35),
                   SDL2pp::Rect(pos.first, pos.second, size, size));
}

void JumpingSniperRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites,
                   SDL2pp::Rect(11, 391, 30, 29),
                   SDL2pp::Rect(pos.first, pos.second, size, size));
}

ActorRendererFactory::ActorRendererFactory(SDL2pp::Renderer *renderer,
                                           Camera &camera) : renderer(renderer),
                                                             camera(camera){
    enemy_sprites = new SDL2pp::Texture(*renderer, "resources/mm3_enemysheet."
            "png");
    actor_renderers["Met"] = MET_R;
    actor_renderers["Bumby"] = BUMBY_R;
    actor_renderers["Sniper"] = SNIPER_R;
    actor_renderers["JumpingSniper"] = JSNIPER_R;
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
        case BUMBY_R:
            actor_renderer = new BumbyRenderer(renderer, enemy_sprites, camera,
                                             pos_x, pos_y);
            break;
        case SNIPER_R:
            actor_renderer = new SniperRenderer(renderer, enemy_sprites, camera,
                                             pos_x, pos_y);
            break;
        case JSNIPER_R:
            actor_renderer = new JumpingSniperRenderer(renderer, enemy_sprites,
                                                       camera, pos_x, pos_y);
            break;
        default:
            throw "ERROR: Non-existint actor renderer!";
    }
    return actor_renderer;
}
