#include "ActorRenderer.h"

ActorRenderer::ActorRenderer(SDL2pp::Renderer *renderer) : renderer(renderer) {
    sprites = new SDL2pp::Texture(*renderer, "resources/mm3_enemysheet.png");
}

void ActorRenderer::renderMet(int dest_x, int dest_y, int run_phase) {
    // TODO: put correct coordinates to the met sprite
    renderer->Copy(*sprites,
                   SDL2pp::Rect(57, 17, 18, 19),
                   SDL2pp::Rect(dest_x, dest_y - 19, 50, 50));
}

ActorRenderer::~ActorRenderer() {
    delete sprites;
}
