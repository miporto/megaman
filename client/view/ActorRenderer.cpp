#include "ActorRenderer.h"

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
               SDL2pp::Rect(dest_x, renderer->GetOutputHeight() - dest_y -
 50, 50, 50));
//    renderer->Copy(*megaman_sprites, SDL2pp::Rect(103, 10, 32, 28),
//               SDL2pp::Rect(300, 300 - 50, 50, 50));
}
void ActorRenderer::renderMet(int dest_x, int dest_y, int dir_x, int dir_y) {
    // TODO: put correct coordinates to the met sprite
    renderer->Copy(*sprites,
                   SDL2pp::Rect(57, 17, 18, 19),
                   SDL2pp::Rect(dest_x, renderer->GetOutputHeight() - dest_y -
                           50, 50, 50));
}

void ActorRenderer::render_pellet(int dest_x, int dest_y, int dir_x,
                                  int dir_y) {
    SDL_Rect fillRect = {dest_x, renderer->GetOutputHeight() - dest_y - 50, 5,
                         5};
    SDL_SetRenderDrawColor(renderer->Get(), 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer->Get(), &fillRect);
}
ActorRenderer::~ActorRenderer() {
    delete sprites;
}
