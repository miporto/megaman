#ifndef MEGAMAN_MEGAMANRENDERER_H
#define MEGAMAN_MEGAMANRENDERER_H

#include <SDL2pp/SDL2pp.hh>

class MegamanRenderer {
public:
    explicit MegamanRenderer(SDL2pp::Renderer* renderer);
    void render(int dest_x, int dest_y);
    ~MegamanRenderer();
private:
    SDL2pp::Renderer* renderer;
    SDL2pp::Texture* sprites;
    int run_phase;
};

#endif //MEGAMAN_MEGAMANRENDERER_H
