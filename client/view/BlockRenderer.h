#ifndef MEGAMAN_BLOCKRENDERER_H
#define MEGAMAN_BLOCKRENDERER_H

#include <SDL2pp/SDL2pp.hh>

#include "TileRenderer.h"

class BlockRenderer {
public:
    explicit BlockRenderer(SDL2pp::Renderer* renderer);
    void render(int dest_x, int dest_y);
    virtual ~BlockRenderer();
private:
    SDL2pp::Renderer* renderer;
    SDL2pp::Texture* sprites;
};


#endif //MEGAMAN_BLOCKRENDERER_H
