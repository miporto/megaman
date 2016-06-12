#ifndef MEGAMAN_BLOCKRENDERER_H
#define MEGAMAN_BLOCKRENDERER_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <string>
#include <utility>
#include "Camera.h"

class TileRenderer;
typedef std::map<int, TileRenderer *> TileRenderers2;
typedef std::pair<int, int> AdjustedPos;
enum TileRendererType {
    BLOCK_R,
    STAIRS_R,
    PELLET_R,
    SPIKE_R,
    DOOR_R
};

class TileRenderer {
public:
    TileRenderer(SDL2pp::Renderer *renderer, SDL2pp::Texture *sprites,
                      Camera &camera, float pos_x, float pos_y);
    void update(float pos_x, float pos_y);
    virtual void render() = 0;
    virtual ~TileRenderer() { }

protected:
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *sprites;
    Camera &camera;
    float pos_x;
    float pos_y;
};

class BlockRenderer : public TileRenderer {
public:
    using TileRenderer::TileRenderer;
    void render();
};

class StairsRenderer : public TileRenderer {
public:
    using TileRenderer::TileRenderer;
    void render();
};

class SpikeRenderer : public TileRenderer {
public:
    using TileRenderer::TileRenderer;
    void render();
};

class BossDoorRenderer : public TileRenderer {
public:
    using TileRenderer::TileRenderer;
    void render();
};

class PelletRenderer : public TileRenderer {
public:
    using TileRenderer::TileRenderer;
    void render();
};

class TileRendererFactory {
public:
    TileRendererFactory(SDL2pp::Renderer *renderer, Camera &camera);
    TileRenderer* build_tile_renderer(std::string tile_type, float pos_x,
                                       float pos_y);
    virtual ~TileRendererFactory() {}
private:
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *sprites;
    SDL2pp::Texture *boss_door_sprites;
    Camera &camera;
    std::map<std::string, TileRendererType> tile_renderers;
};

#endif //MEGAMAN_BLOCKRENDERER_H
