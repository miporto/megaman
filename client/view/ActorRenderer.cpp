#include <string>
#include "ActorRenderer.h"

ActorRendererr::ActorRendererr(SDL2pp::Renderer *renderer,
                               SDL2pp::Texture *sprites, float pos_x, float
                               pos_y) :
        renderer(renderer), sprites(sprites), pos_x(pos_x), pos_y(pos_y),
        dir_x(0), dir_y(0) { }

void ActorRendererr::update(float pos_x, float pos_y, int dir_x, int
dir_y) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->dir_x = dir_x;
    this->dir_y = dir_y;
}

void MetRenderer::render() {
    float y = pos_y * 50 + 50;
    renderer->Copy(*sprites,
                   SDL2pp::Rect(57, 17, 18, 19),
                   SDL2pp::Rect((int) pos_x * 50, renderer->GetOutputHeight() -
                                                  (int) y, 50, 50));
}

void MegaManRenderer::render() {
    float y = pos_y * 50 + 50;
    renderer->Copy(*sprites, SDL2pp::Rect(103, 10, 32, 28),
                   SDL2pp::Rect((int) pos_x * 50,
                                renderer->GetOutputHeight() -
                                (int) y, 50, 50));
}

ActorRendererFactory::ActorRendererFactory(SDL2pp::Renderer *renderer) :
        renderer(renderer){
    sprites = new SDL2pp::Texture(*renderer, "resources/8bitmegaman."
            "png");
    actor_renderers["Met"] = MET_R;
    actor_renderers["MegaMan"] = MEGAMAN_R;
}

ActorRendererr *ActorRendererFactory::build_actor_renderer(std::string
                                                           tile_type,
                                                           float pos_x, float
                                                           pos_y) {
    ActorRendererr *actor_renderer = NULL;
    ActorRendererType tile_renderer_id = actor_renderers[tile_type];
    switch (tile_renderer_id) {
        case MET_R:
            actor_renderer = new MetRenderer(renderer, sprites, pos_x, pos_y);
            break;
        case MEGAMAN_R:
            actor_renderer = new MegaManRenderer(renderer, sprites, pos_x,
                                                pos_y);
            break;
        default:
            throw "ERROR: Non-existint actor renderer!";
    }
    return actor_renderer;
}

// Old stuff
ActorRenderer::ActorRenderer(SDL2pp::Renderer *renderer) : renderer(renderer) {
    renderers["Met"] = &ActorRenderer::renderMet;
    renderers["MegaMan"] = &ActorRenderer::render_megaman;
    renderers["Pellet"] = &ActorRenderer::render_pellet;
    sprites = new SDL2pp::Texture(*renderer, "resources/mm3_enemysheet.png");
    megaman_sprites = new SDL2pp::Texture(*renderer, "resources/8bitmegaman"
            ".png");
}

ActorRenderers ActorRenderer::get_renderers() {
    return renderers;
}

void ActorRenderer::render_megaman(int dest_x, int dest_y, int dir_x,
                                   int dir_y) {
    renderer->Copy(*megaman_sprites, SDL2pp::Rect(103, 10, 32, 28),
                   SDL2pp::Rect(dest_x + dest_x * 50,
                                renderer->GetOutputHeight() -
                                dest_y * 50 -
                                50, 50, 50));
//    renderer->Copy(*megaman_sprites, SDL2pp::Rect(103, 10, 32, 28),
//               SDL2pp::Rect(300, 300 - 50, 50, 50));
}

void ActorRenderer::renderMet(int dest_x, int dest_y, int dir_x, int dir_y) {
    // TODO: put correct coordinates to the met sprite
    renderer->Copy(*sprites,
                   SDL2pp::Rect(57, 17, 18, 19),
                   SDL2pp::Rect(dest_x + dest_x * 50, renderer->GetOutputHeight
                                        () -
                                                      dest_y * 50 - 50, 50,
                                50));
}

void ActorRenderer::render_pellet(int dest_x, int dest_y, int dir_x,
                                  int dir_y) {
    SDL_Rect fillRect = {dest_x + dest_x * 50, renderer->GetOutputHeight() -
                                               dest_y - 50, 5, 5};
    SDL_SetRenderDrawColor(renderer->Get(), 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer->Get(), &fillRect);
}

ActorRenderer::~ActorRenderer() {
    delete sprites;
}
