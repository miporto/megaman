#ifndef MEGAMAN_METRENDERER_H
#define MEGAMAN_METRENDERER_H

#include <SDL2pp/SDL2pp.hh>

class MetRenderer {
public:
    explicit MetRenderer(SDL2pp::Renderer* renderer);
    void render(int dest_x, int dest_y, int run_phase);
    virtual ~MetRenderer();
private:
    SDL2pp::Renderer* renderer;
    SDL2pp::Texture* sprites;
};


#endif //MEGAMAN_METRENDERER_H
