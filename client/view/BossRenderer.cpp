#include <string>

#include "BossRenderer.h"
#include "StageElementsConstants.h"

BossRenderer::BossRenderer(SDL2pp::Renderer *renderer, SDL2pp::Texture *sprites,
                           Camera &camera, float pos_x, float pos_y,
                           int energy) : renderer(renderer),
                                         sprites(sprites),
                                         camera(camera),
                                         pos_x(pos_x),
                                         pos_y(pos_y),
                                         dir_x(0), dir_y(0),
                                         initial_energy(energy),
                                         actual_energy(energy) { }

void BossRenderer::update(float pos_x, float pos_y, int dir_x, int dir_y,
                          int energy) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->dir_x = dir_x;
    this->dir_y = dir_y;
    this->actual_energy = energy;
}

void BossRenderer::render_energy(int size) {
    int energy_percent = 100 - actual_energy;
//    std::cout << "Energy: " << actual_energy << ", " << energy_percent <<
//            std::endl;
    renderer->SetDrawColor(0xff, 0xff, 0);
    renderer->FillRect(renderer->GetOutputWidth() - 150, 10,
                       renderer->GetOutputWidth() - energy_percent, size/2);
}

void BombManRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites, SDL2pp::Rect(123, 12, 24, 24),
                   SDL2pp::Rect(pos.first , pos.second, size, size));
    render_energy(size);
}

void MagnetManRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites, SDL2pp::Rect(6, 10, 28, 29),
                   SDL2pp::Rect(pos.first , pos.second, size, size));
    render_energy(size);
}

void SparkManRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites, SDL2pp::Rect(54, 17, 30, 31),
                   SDL2pp::Rect(pos.first , pos.second, size, size));
    render_energy(size);
}

void RingManRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites, SDL2pp::Rect(7, 5, 25, 30),
                   SDL2pp::Rect(pos.first , pos.second, size, size));
    render_energy(size);
}

void FireManRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites, SDL2pp::Rect(31, 11, 24, 31),
                   SDL2pp::Rect(pos.first , pos.second, size, size));
    render_energy(size);
}

BossRendererFactory::BossRendererFactory(SDL2pp::Renderer *renderer,
                                         Camera &camera) : renderer(renderer),
                                                           camera(camera){
    bomb_man_sprites = new SDL2pp::Texture(*renderer, "resources/bombman.gif");
    magnet_man_sprites = new SDL2pp::Texture(*renderer, "resources/magnetman"
            ".gif");
    spark_man_sprites = new SDL2pp::Texture(*renderer, "resources/sparkman"
            ".gif");
    ring_man_sprites = new SDL2pp::Texture(*renderer, "resources/ringman.gif");
    fire_man_sprites = new SDL2pp::Texture(*renderer, "resources/fireman.gif");

    boss_renderers[BOMBMAN] = BBOMBMAN_R;
    boss_renderers[MAGNETMAN] = MAGNETMAN_R;
    boss_renderers[SPARKMAN] = SPARKMAN_R;
    boss_renderers[RINGMAN] = RINGMAN_R;
    boss_renderers[FIREMAN] = FIREMAN_R;
}

BossRenderer* BossRendererFactory::build_boss_renderer(std::string tile_type,
                                                       float pos_x, float pos_y,
                                                       int energy) {
    BossRenderer *actor_renderer = NULL;
    BossRendererType tile_renderer_id = boss_renderers[tile_type];
    switch (tile_renderer_id) {
        case BBOMBMAN_R:
            actor_renderer = new BombManRenderer(renderer, bomb_man_sprites,
                                                  camera, pos_x, pos_y, energy);
            break;
        case MAGNETMAN_R:
            actor_renderer = new MagnetManRenderer(renderer, magnet_man_sprites,
                                                   camera, pos_x, pos_y,
                                                   energy);
            break;
        case SPARKMAN_R:
            actor_renderer = new SparkManRenderer(renderer, spark_man_sprites,
                                                  camera, pos_x, pos_y, energy);
            break;
        case RINGMAN_R:
            actor_renderer = new RingManRenderer(renderer, ring_man_sprites,
                                                       camera, pos_x, pos_y,
                                                       energy);
            break;
        case FIREMAN_R:
            actor_renderer = new FireManRenderer(renderer, fire_man_sprites,
                                                 camera, pos_x, pos_y, energy);
            break;
        default:
            throw "ERROR: Non-existint boss renderer!";
    }
    return actor_renderer;
}

BossRendererFactory::~BossRendererFactory(){
    delete bomb_man_sprites;
    delete magnet_man_sprites;
    delete spark_man_sprites;
    delete ring_man_sprites;
    delete fire_man_sprites;
}
