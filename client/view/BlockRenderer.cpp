#include "BlockRenderer.h"

void BlockRenderer::render(int dest_x, int dest_y) {
    // TODO: put correct coordinates to the block sprite
    renderer->Copy(*sprites,
                   SDL2pp::Rect(8, 11, 50, 50),
                   SDL2pp::Rect(dest_x, dest_y - 50, 50, 50));
}
