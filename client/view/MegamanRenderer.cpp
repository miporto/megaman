#include <SDL2pp/SDL2pp.hh>

#include "MegamanRenderer.h"

MegamanRenderer::MegamanRenderer(SDL2pp::Renderer* renderer) {
    sprites = new SDL2pp::Texture(*renderer, "resources/M484SpaceSoldier"
            ".png");
}
