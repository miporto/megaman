#include <string>

#include "Camera.h"
#include "MegaManRenderer.h"

MMegaManRenderer::MMegaManRenderer(SDL2pp::Renderer *renderer, Camera &camera,
                                   float pos_x, float pos_y, int energy,
                                   const std::string &name) : renderer(renderer),
                                                              camera(camera),
                                                              pos_x(pos_x),
                                                              pos_y(pos_y),
                                                              dir_x(0), dir_y(0),
                                                              initial_energy(energy),
                                                              actual_energy(energy),
                                                              name(name){
    sprites = new SDL2pp::Texture(*renderer, "resources/8bitmegaman.png");
}

void MMegaManRenderer::update(float pos_x, float pos_y, int dir_x, int dir_y,
                          int energy) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->dir_x = dir_x;
    this->dir_y = dir_y;
    this->actual_energy = energy;
}

void MMegaManRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites, SDL2pp::Rect(103, 10, 21, 24),
                   SDL2pp::Rect(pos.first , pos.second, size, size));
}

float MMegaManRenderer::get_x() {
    return pos_x;
}

float MMegaManRenderer::get_y() {
    return pos_y;
}

MMegaManRenderer::~MMegaManRenderer() {
    delete sprites;
}
