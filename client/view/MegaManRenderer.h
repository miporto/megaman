#ifndef MEGAMAN_MEGAMANRENDERER_H
#define MEGAMAN_MEGAMANRENDERER_H


#include <extern/libSDL2pp/SDL2pp/Renderer.hh>
#include <string>

#include "Camera.h"

class Camera;
class MMegaManRenderer {
public:
    MMegaManRenderer(SDL2pp::Renderer *renderer, Camera &camera, float pos_x,
                     float pos_y, int energy, const std::string &name);
    void update(float pos_x, float pos_y, int dir_x, int dir_y, int energy);
    void render();
    float get_x();
    float get_y();
    ~MMegaManRenderer();
private:
    void render_energy();
    void render_name();
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *sprites;
    Camera &camera;
    float pos_x;
    float pos_y;
    int dir_x;
    int dir_y;
    int initial_energy;
    int actual_energy;
    const std::string &name;
};


#endif //MEGAMAN_MEGAMANRENDERER_H
