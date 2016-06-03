#include <SDL2pp/SDL2pp.hh>

#include "BlockRenderer.h"
#include "common/StageParser.h"
#include "StageRenderer.h"

StageRenderer::StageRenderer(SDL2pp::Renderer *renderer) : renderer(renderer)
        , block(renderer) {
    background = new SDL2pp::Texture(*renderer, "resources/background.png");
}

void StageRenderer::render() {
    renderer->Copy(*background);
    block.render(0, renderer->GetOutputHeight() - 50);
    block.render(50, renderer->GetOutputHeight() - 50);
    block.render(100, renderer->GetOutputHeight() - 50);
}

StageRenderer::~StageRenderer() {
    delete background;
}
