#ifndef MEGAMAN_MEGAMANRENDERER_H
#define MEGAMAN_MEGAMANRENDERER_H


#include <SDL2pp/SDL2pp.hh>
#include <string>

#include "Camera.h"

class Camera;
class MegaManRenderer {
public:
    MegaManRenderer(SDL2pp::Renderer *renderer, Camera &camera, float pos_x,
                     float pos_y, int energy, const std::string &name);
    void update(float pos_x, float pos_y, int dir_x, int dir_y, float energy);
    void render();
    float get_x();
    float get_y();
    ~MegaManRenderer();
private:
    void render_energy(int size);
    void render_name();
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *sprites;
    Camera &camera;
    float pos_x;
    float pos_y;
    float prev_x;
    float prev_y;
    int running_phase;
    int dir_x;
    int dir_y;
    float actual_energy;
    const std::string &name;
};


#endif //MEGAMAN_MEGAMANRENDERER_H
