#include "ActorRenderer.h"

ActorRenderer::ActorRenderer(SDL2pp::Renderer *renderer) : renderer(renderer) {
    renderers["Met"] = &ActorRenderer::renderMet;
    renderers["Megaman"] = &ActorRenderer::render_megaman;
    sprites = new SDL2pp::Texture(*renderer, "resources/mm3_enemysheet.png");
    megaman_sprites = new SDL2pp::Texture(*renderer, "resources/8bitmegaman"
            ".png");
}

ActorRenderers ActorRenderer::get_renderers() {
    return renderers;
}

void ActorRenderer::render_megaman(int dest_x, int dest_y, int dir_x,
                                   int dir_y) {
    renderer->Copy(*megaman_sprites, SDL2pp::Rect(127, 286, 32, 28),
               SDL2pp::Rect(dest_x, dest_y - 50, 50, 50));
}
void ActorRenderer::renderMet(int dest_x, int dest_y, int dir_x, int dir_y) {
    // TODO: put correct coordinates to the met sprite
    renderer->Copy(*sprites,
                   SDL2pp::Rect(57, 17, 18, 19),
                   SDL2pp::Rect(dest_x, dest_y - 19, 50, 50));
}

ActorRenderer::~ActorRenderer() {
    delete sprites;
}
