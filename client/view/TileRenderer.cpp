#include <SDL2pp/SDL2pp.hh>
#include <string>

#include "TileRenderer.h"

TileRendererr::TileRendererr(SDL2pp::Renderer *renderer,
                             SDL2pp::Texture *sprites, int pos_x,
                             int pos_y) :
        renderer(renderer), sprites(sprites), pos_x(pos_x), pos_y(pos_y) { }

void TileRendererr::update(int pos_x, int pos_y) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

void BlockRenderer::render() {
    renderer->Copy(*sprites,
                   SDL2pp::Rect(52, 119, 16, 16),
                   SDL2pp::Rect(pos_x, pos_y, 50, 50));
}

void StairsRenderer::render() {
    renderer->Copy(*sprites,
                   SDL2pp::Rect(35, 85, 16, 16),
                   SDL2pp::Rect(pos_x, pos_y, 50, 50));
}

void PelletRenderer::render() {
    SDL_Rect fillRect = {pos_x, renderer->GetOutputHeight() -
                                               pos_y, 5, 5};
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
                                                        int pos_x, int
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
// Old stuff
TileRenderer::TileRenderer(SDL2pp::Renderer *renderer) :
        renderer(renderer) {
    // TODO: be coherent with identifiers of json file
    renderers["Block"] = &TileRenderer::renderBlock;
    renderers["Stairs"] = &TileRenderer::renderStairs;
    sprites = new SDL2pp::Texture(*renderer, "resources/mm3_8boss_shadowman."
            "png");
}

TileRenderers TileRenderer::get_renderers() {
    return renderers;
}

void TileRenderer::renderBlock(int dest_x, int dest_y) {
    renderer->Copy(*sprites,
                   SDL2pp::Rect(52, 119, 16, 16),
                   SDL2pp::Rect(dest_x * 50, renderer->GetOutputHeight()
                                             - dest_y * 50 - 50, 50, 50));
}

void TileRenderer::renderStairs(int dest_x, int dest_y) {
    renderer->Copy(*sprites,
                   SDL2pp::Rect(35, 85, 16, 16),
                   SDL2pp::Rect(dest_x * 50, renderer->GetOutputHeight()
                                             - dest_y * 50 - 50, 50, 50));
}

TileRenderer::~TileRenderer() {
    delete sprites;
}
