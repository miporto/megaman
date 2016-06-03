#include "TileRenderer.h"

TileRenderer::TileRenderer(SDL2pp::Renderer *renderer) : renderer(renderer) {
    // TODO: search tile sprites
    sprites = new SDL2pp::Texture(*renderer, "resources/M484SpaceSoldier"
            ".png");
}

TileRenderer::~TileRenderer() {
    delete sprites;
}
