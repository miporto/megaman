#ifndef MEGAMAN_TILERENDERER_H
#define MEGAMAN_TILERENDERER_H

#include <SDL2pp/SDL2pp.hh>

class TileRenderer {
public:
    explicit TileRenderer(SDL2pp::Renderer* renderer);
    virtual void render(int dest_x, int dest_y) = 0;
    ~TileRenderer();
protected:
    SDL2pp::Renderer* renderer;
    SDL2pp::Texture* sprites;
};


#endif //MEGAMAN_TILERENDERER_H
