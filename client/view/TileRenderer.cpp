#include <SDL2pp/SDL2pp.hh>

#include "TileRenderer.h"

TileRenderer::TileRenderer(SDL2pp::Renderer* renderer) :
        renderer(renderer) {
    // TODO: be coherent with identifiers of json file
    renderers["block"] = &TileRenderer::renderBlock;
    renderers["stairs"] = &TileRenderer::renderStairs;
    sprites = new SDL2pp::Texture(*renderer, "resources/mm3_8boss_shadowman."
            "png");
}

tile_renderers_t TileRenderer::get_renderers() {
    return renderers;
}
void TileRenderer::renderBlock(int dest_x, int dest_y) {
    renderer->Copy(*sprites,
                   SDL2pp::Rect(52, 119, 16, 16),
                   SDL2pp::Rect(dest_x, dest_y - 16, 50, 50));
}

void TileRenderer::renderStairs(int dest_x, int dest_y) {
    renderer->Copy(*sprites,
                   SDL2pp::Rect(35, 85, 16, 16),
                   SDL2pp::Rect(dest_x, dest_y - 16, 50, 50));
}
TileRenderer::~TileRenderer() {
    delete sprites;
}
