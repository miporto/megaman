#ifndef MEGAMAN_BLOCKRENDERER_H
#define MEGAMAN_BLOCKRENDERER_H

#include "TileRenderer.h"

class BlockRenderer : public TileRenderer {
public:
    explicit BlockRenderer(SDL2pp::Renderer* renderer);
    void render(int dest_x, int dest_y) override;
};


#endif //MEGAMAN_BLOCKRENDERER_H
