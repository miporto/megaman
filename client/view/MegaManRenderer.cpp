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
                                                              running_phase(0),
                                                              dir_x(0), dir_y(0),
                                                              actual_energy(energy),
                                                              name(name){
    sprites = new SDL2pp::Texture(*renderer, "resources/8bitmegaman.png");
//    phases.push_back(new SDL2pp::Rect(103, 10, 21, 24));
//    phases.push_back(new SDL2pp::Rect(133, 10, 21, 24));
//    phases.push_back(new SDL2pp::Rect(160, 10, 20, 24));
    phases.push_back(new SDL2pp::Rect(188, 12, 24, 22));
    phases.push_back(new SDL2pp::Rect(218, 10, 16, 23));
    phases.push_back(new SDL2pp::Rect(239, 12, 21, 22));
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
        renderer->Copy(*sprites, SDL2pp::Rect(meg_x, meg_y, size_meg_x, size_meg_y),
                       SDL2pp::Rect(pos.first , pos.second, size, size), 0.0,
                       SDL2pp::NullOpt, flip);
    } else if (prev_x != pos_x) {
        SDL2pp::Rect *rect = phases.at(running_phase % phases.size());
        if (prev_x > pos_x) {
            flip = SDL_FLIP_HORIZONTAL;
        }
        renderer->Copy(*sprites, *rect,
                       SDL2pp::Rect(pos.first , pos.second, size, size), 0.0,
                       SDL2pp::NullOpt, flip);
        ++running_phase;
    } else {
        renderer->Copy(*sprites, SDL2pp::Rect(meg_x, meg_y, size_meg_x, size_meg_y),
                       SDL2pp::Rect(pos.first , pos.second, size, size), 0.0,
                       SDL2pp::NullOpt, flip);
        running_phase = 0;
    }
    render_energy(size, pos.first, pos.second);
    render_name(pos.first, pos.second);
}

void MegaManRenderer::render_energy(int size, int x, int y) {
    float energy = actual_energy*size*1.5/100;
    float size_y =  y-size/1.2;
    renderer->SetDrawColor(34, 139, 34);
    renderer->FillRect(x, y-size, x + (int) energy,(int) size_y);
}

void MegaManRenderer::render_name(int x, int y) {
    SDL2pp::SDLTTF ttf;
    SDL2pp::Font font("resources/megaman_2.ttf", 10);
    SDL2pp::Texture text_sprite(
            *renderer,
            font.RenderText_Blended(name, SDL_Color{255, 255, 255, 255}));
    int text_w= text_sprite.GetWidth();
    int text_h = text_sprite.GetHeight();
    renderer->Copy(text_sprite, SDL2pp::NullOpt, SDL2pp::Rect(x + text_w/2,
                                                              y - text_h,
                                                              text_w, text_h));
}
float MegaManRenderer::get_x() {
    return pos_x;
}

float MegaManRenderer::get_y() {
    return pos_y;
}

MegaManRenderer::~MegaManRenderer() {
    for (auto const &it: phases) {
        delete it;
    }
    phases.clear();
    delete sprites;
}
