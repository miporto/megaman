#include <SDL2pp/SDL2pp.hh>

#include "BlockRenderer.h"
#include "common/StageParser.h"
#include "StageRenderer.h"

StageRenderer::StageRenderer(SDL2pp::Renderer *renderer) : renderer(renderer)
        , block(renderer), met(renderer) {
    background = new SDL2pp::Texture(*renderer, "resources/background.png");
}

void StageRenderer::render() {
    renderer->Copy(*background);
    tile_renderers_t tile_renderers = block.get_renderers();
    (block.*(tile_renderers["block"]))(0, renderer->GetOutputHeight() - 40);
    (block.*(tile_renderers["block"]))(50, renderer->GetOutputHeight() - 40);
    (block.*(tile_renderers["block"]))(100, renderer->GetOutputHeight() - 40);
//    block.render(0, renderer->GetOutputHeight() - 50);
//    block.render(50, renderer->GetOutputHeight() - 50);
//    block.render(100, renderer->GetOutputHeight() - 50);
    met.render(100, renderer->GetOutputHeight() - 100, 0);
}

StageRenderer::~StageRenderer() {
    delete background;
}
