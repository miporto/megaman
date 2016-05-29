#include <SDL2pp/SDL2pp.hh>

#include "MegamanRenderer.h"

MegamanRenderer::MegamanRenderer(SDL2pp::Renderer* renderer) :
        renderer(renderer), run_phase(-1) {
    sprites = new SDL2pp::Texture(*renderer, "resources/M484SpaceSoldier"
            ".png");
}
