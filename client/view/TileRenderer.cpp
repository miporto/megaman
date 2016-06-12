#include <SDL2pp/SDL2pp.hh>
#include <string>

#include "TileRenderer.h"
#include "Camera.h"

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
    SDL_Rect fillRect = {pos.first, pos.first, 5, 5};
    SDL_SetRenderDrawColor(renderer->Get(), 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer->Get(), &fillRect);
}

TileRendererFactory::TileRendererFactory(SDL2pp::Renderer *renderer,
                                         Camera &camera) : renderer(renderer),
                                                           camera(camera) {
    sprites = new SDL2pp::Texture(*renderer, "resources/mm3_8boss_shadowman."
            "png");
    boss_door_sprites = new SDL2pp::Texture(*renderer, "resources/boss_door"
            ".png");
    tile_renderers["Block"] = BLOCK_R;
    tile_renderers["Stairs"] = STAIRS_R;
    tile_renderers["Pellet"] = PELLET_R;
    tile_renderers["Spike"] = SPIKE_R;
    tile_renderers["Door"] = DOOR_R;
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
