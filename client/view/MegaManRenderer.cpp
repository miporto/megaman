#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "Camera.h"
#include "MegaManRenderer.h"

MegaManRenderer::MegaManRenderer(SDL2pp::Renderer *renderer, Camera &camera,
                                   float pos_x, float pos_y, int energy,
                                   const std::string &name) : renderer(renderer),
                                                              camera(camera),
                                                              pos_x(pos_x),
                                                              pos_y(pos_y),
                                                              prev_x(0),
                                                              prev_y(0),
                                                              dir_x(0), dir_y(0),
                                                              actual_energy(energy),
                                                              name(name){
    sprites = new SDL2pp::Texture(*renderer, "resources/8bitmegaman.png");
}

void MegaManRenderer::update(float pos_x, float pos_y, int dir_x, int dir_y,
                          float energy) {
    prev_x = this->pos_x;
    prev_y = this->pos_y;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->dir_x = dir_x;
    this->dir_y = dir_y;
    this->actual_energy = energy;
}

void MegaManRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    int meg_x = 103;
    int meg_y = 10;
    int size_meg_x = 21;
    int size_meg_y = 24;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (prev_y < pos_y) {
        meg_x = 265;
        meg_y = 4;
        size_meg_x = 26;
        size_meg_y = 30;
    } else if (prev_x != pos_x) {
        meg_x = 103;
        meg_y = 10;
        size_meg_x = 21;
        size_meg_y = 24;
        if (prev_x > pos_x) {
            flip = SDL_FLIP_HORIZONTAL;
        }
    }
    renderer->Copy(*sprites, SDL2pp::Rect(meg_x, meg_y, size_meg_x, size_meg_y),
                   SDL2pp::Rect(pos.first , pos.second, size, size), 0.0,
                   SDL2pp::NullOpt, flip);
    render_energy(size);
}

void MegaManRenderer::render_energy(int size) {
    float energy_percent = actual_energy;
    renderer->SetDrawColor(34, 139, 34);
    renderer->FillRect(10, 10, (int) energy_percent, size/2);
}
float MegaManRenderer::get_x() {
    return pos_x;
}

float MegaManRenderer::get_y() {
    return pos_y;
}

MegaManRenderer::~MegaManRenderer() {
    delete sprites;
}
