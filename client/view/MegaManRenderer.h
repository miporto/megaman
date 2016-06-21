#ifndef MEGAMAN_MEGAMANRENDERER_H
#define MEGAMAN_MEGAMANRENDERER_H


#include <SDL2pp/SDL2pp.hh>
#include <string>
#include <vector>

#include "Camera.h"

class Camera;
class MegaManRenderer {
public:
    MegaManRenderer(SDL2pp::Renderer *renderer, Camera &camera, float pos_x,
                     float pos_y, int energy, const std::string &name);
    void update(float pos_x, float pos_y, int dir_x, int dir_y, float energy, bool respawn);
    void render();
    std::string get_name();
    float get_x();
    float get_y();
    ~MegaManRenderer();

private:
    void render_energy(int size, int x, int y);
    void render_name(int x, int y);
    void render_ready_msg();
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
    bool respawn;
    const std::string name;
    std::vector<SDL2pp::Rect*> phases;
};


#endif //MEGAMAN_MEGAMANRENDERER_H
