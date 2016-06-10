#include <SDL2pp/SDL2pp.hh>
#include <string>

#include "TileRenderer.h"

TileRendererr::TileRendererr(SDL2pp::Renderer *renderer,
                             SDL2pp::Texture *sprites, float pos_x,
                             float pos_y) :
        renderer(renderer), sprites(sprites), pos_x(pos_x), pos_y(pos_y) { }

AdjustedPos TileRendererr::adjust_position(float x, float y) {
    AdjustedPos adjusted_pos;
    int adj_x = (int) x*50;
    int adj_y = renderer->GetOutputHeight() - (int) (y + 1)*50;
    adjusted_pos.first = adj_x;
    adjusted_pos.second = adj_y;
    return adjusted_pos;
}

void TileRendererr::update(float pos_x, float pos_y) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

void BlockRenderer::render() {
    AdjustedPos pos = adjust_position(pos_x, pos_y);
    renderer->Copy(*sprites,
                   SDL2pp::Rect(52, 119, 16, 16),
                   SDL2pp::Rect(pos.first, pos.second, 50, 50));
}

void StairsRenderer::render() {
    AdjustedPos pos = adjust_position(pos_x, pos_y);
    renderer->Copy(*sprites,
                   SDL2pp::Rect(35, 85, 16, 16),
                   SDL2pp::Rect(pos.first, pos.second, 50, 50));
}

void PelletRenderer::render() {
    AdjustedPos pos = adjust_position(pos_x, pos_y);
    SDL_Rect fillRect = {pos.first, pos.first, 5, 5};
    SDL_SetRenderDrawColor(renderer->Get(), 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer->Get(), &fillRect);
}

TileRendererFactory::TileRendererFactory(SDL2pp::Renderer * renderer) :
        renderer(renderer) {
    sprites = new SDL2pp::Texture(*renderer, "resources/mm3_8boss_shadowman."
            "png");
    tile_renderers["Block"] = BLOCK_R;
    tile_renderers["Stairs"] = STAIRS_R;
    tile_renderers["Pellet"] = PELLET_R;
}
TileRendererr* TileRendererFactory::build_tile_renderer(std::string tile_type,
                                                        float pos_x, float
                                                        pos_y) {
    TileRendererr *tile_renderer = NULL;
    TileRendererType tile_renderer_id = tile_renderers[tile_type];
    switch (tile_renderer_id){
        case BLOCK_R:
            tile_renderer = new BlockRenderer(renderer,sprites, pos_x, pos_y);
            break;
        case STAIRS_R:
            tile_renderer = new StairsRenderer(renderer, sprites, pos_x, pos_y);
            break;
        case PELLET_R:
            tile_renderer = new PelletRenderer(renderer, sprites, pos_x, pos_y);
            break;
        default:
            throw "ERROR: Non-existint tile renderer!";
    }
    return tile_renderer;
}
