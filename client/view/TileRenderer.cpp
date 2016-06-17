#include <SDL2pp/SDL2pp.hh>
#include <string>

#include "TileRenderer.h"
#include "Camera.h"
#include "StageElementsConstants.h"

TileRenderer::TileRenderer(SDL2pp::Renderer *renderer,
                             SDL2pp::Texture *sprites, Camera &camera,
                             float pos_x, float pos_y) : renderer(renderer),
                                                         sprites(sprites),
                                                         camera(camera),
                                                         pos_x(pos_x),
                                                         pos_y(pos_y) {}

void TileRenderer::update(float pos_x, float pos_y) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

void BlockRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites,
                   SDL2pp::Rect(52, 119, 16, 16),
                   SDL2pp::Rect(pos.first, pos.second, size, size));
}

void StairsRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites,
                   SDL2pp::Rect(35, 85, 16, 16),
                   SDL2pp::Rect(pos.first, pos.second, size, size));
}

void SpikeRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites,
                   SDL2pp::Rect(103, 238, 16, 16),
                   SDL2pp::Rect(pos.first, pos.second, size, size));
}

void BossDoorRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites,
                   SDL2pp::Rect(0, 66, 267, 334),
                   SDL2pp::Rect(pos.first, pos.second, size, size));
}

void PelletRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    renderer->SetDrawColor(0xFF, 0, 0);
    renderer->FillRect(pos.first, pos.second, pos.first + 10, pos.second + 10);
}

void BombRenderer::render() {
    AdjustedPos pos = camera.adjust_position(pos_x, pos_y);
    int size = camera.adjust_size();
    renderer->Copy(*sprites, SDL2pp::Rect(59, 62, 20, 20),
                   SDL2pp::Rect(pos.first , pos.second, size/2, size/2));
}

void PlasmaRenderer::render() {
    AdjustedPos pos = camera.adjust_proyectile_position(pos_x, pos_y);
    renderer->SetDrawColor(0, 0, 0xFF);
    renderer->FillRect(pos.first, pos.second, pos.first + 10, pos.second + 10);
}

TileRendererFactory::TileRendererFactory(SDL2pp::Renderer *renderer,
                                         Camera &camera) : renderer(renderer),
                                                           camera(camera) {
    sprites = new SDL2pp::Texture(*renderer, "resources/mm3_8boss_shadowman."
            "png");
    bomb_sprites = new SDL2pp::Texture(*renderer, "resources/bombman.gif");
    boss_door_sprites = new SDL2pp::Texture(*renderer, "resources/boss_door"
            ".png");
    tile_renderers[BLOCK] = BLOCK_R;
    tile_renderers[STAIRS] = STAIRS_R;
    tile_renderers[PELLET] = PELLET_R;
    tile_renderers[BOMB] = BOMB_R;
    tile_renderers[PLASMA] = PLASMA_R;
    tile_renderers[SPIKE] = SPIKE_R;
    tile_renderers[DOOR] = DOOR_R;
}
TileRenderer* TileRendererFactory::build_tile_renderer(std::string tile_type,
                                                        float pos_x, float
                                                        pos_y) {
    TileRenderer *tile_renderer = NULL;
    TileRendererType tile_renderer_id = tile_renderers[tile_type];
    switch (tile_renderer_id){
        case BLOCK_R:
            tile_renderer = new BlockRenderer(renderer,sprites, camera, pos_x,
                                              pos_y);
            break;
        case STAIRS_R:
            tile_renderer = new StairsRenderer(renderer, sprites, camera,
                                               pos_x, pos_y);
            break;
        case PELLET_R:
            tile_renderer = new PelletRenderer(renderer, sprites, camera,
                                               pos_x, pos_y);
            break;
        case BOMB_R:
            tile_renderer = new BombRenderer(renderer, bomb_sprites, camera,
                                               pos_x, pos_y);
            break;
        case PLASMA_R:
            tile_renderer = new PlasmaRenderer(renderer, sprites, camera,
                                               pos_x, pos_y);
            break;
        case SPIKE_R:
            tile_renderer = new SpikeRenderer(renderer, sprites, camera,
                                               pos_x, pos_y);
            break;
        case DOOR_R:
            tile_renderer = new BossDoorRenderer(renderer, boss_door_sprites,
                                                 camera, pos_x, pos_y);
            break;
        default:
            throw "ERROR: Non-existint tile renderer!";
    }
    return tile_renderer;
}
