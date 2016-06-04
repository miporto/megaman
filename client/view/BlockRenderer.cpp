#include <SDL2pp/SDL2pp.hh>

#include "BlockRenderer.h"

BlockRenderer::BlockRenderer(SDL2pp::Renderer* renderer) :
        renderer(renderer) {
    // TODO: be coherent with identifiers of json file
    renderers["block"] = &BlockRenderer::render;
    sprites = new SDL2pp::Texture(*renderer, "resources/mm3_8boss_shadowman."
            "png");
}

tile_renderers_t BlockRenderer::get_renderers() {
    return renderers;
}
void BlockRenderer::render(int dest_x, int dest_y) {
    renderer->Copy(*sprites,
                   SDL2pp::Rect(52, 119, 16, 16),
                   SDL2pp::Rect(dest_x, dest_y - 16, 50, 50));
}

BlockRenderer::~BlockRenderer() {
    delete sprites;
}
