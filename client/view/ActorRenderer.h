#ifndef MEGAMAN_METRENDERER_H
#define MEGAMAN_METRENDERER_H

#include <SDL2pp/SDL2pp.hh>

class ActorRenderer {
public:
    explicit ActorRenderer(SDL2pp::Renderer* renderer);
    void renderMet(int dest_x, int dest_y, int run_phase);
    virtual ~ActorRenderer();
private:
    SDL2pp::Renderer* renderer;
    SDL2pp::Texture* sprites;
};


#endif //MEGAMAN_METRENDERER_H
