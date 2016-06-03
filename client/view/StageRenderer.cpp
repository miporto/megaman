#include <SDL2pp/SDL2pp.hh>

#include "common/StageParser.h"
#include "StageRenderer.h"

StageRenderer::StageRenderer(SDL2pp::Renderer *renderer) : renderer(renderer) {
    background = new SDL2pp::Texture(*renderer, "resources/background.png");
}

void StageRenderer::render() {
    renderer->Copy(*background);
}

StageRenderer::~StageRenderer() {
    delete background;
}
