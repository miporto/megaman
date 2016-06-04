#include <SDL2pp/SDL2pp.hh>

#include "MegamanRenderer.h"

MegamanRenderer::MegamanRenderer(SDL2pp::Renderer* renderer) :
        renderer(renderer), run_phase(-1) {
    sprites = new SDL2pp::Texture(*renderer, "resources/8bitmegaman.png");
}

void MegamanRenderer::render(int dest_x, int dest_y) {
    // TODO: request more info to be able to draw the proper sprite
    renderer->Copy(*sprites,
                   SDL2pp::Rect(127, 286, 32, 28),
                   SDL2pp::Rect(dest_x, dest_y - 50, 50, 50));
}

MegamanRenderer::~MegamanRenderer(){
    delete sprites;
}
