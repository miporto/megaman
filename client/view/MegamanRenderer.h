#ifndef MEGAMAN_MEGAMANRENDERER_H
#define MEGAMAN_MEGAMANRENDERER_H

#include <SDL2pp/SDL2pp.hh>

class MegamanRenderer {
public:
    explicit MegamanRenderer(SDL2pp::Renderer* renderer);
    void render();
    ~MegamanRenderer();
private:
    SDL2pp::Texture* sprites;
};

#endif //MEGAMAN_MEGAMANRENDERER_H
