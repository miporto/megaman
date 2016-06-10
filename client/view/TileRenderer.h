#ifndef MEGAMAN_BLOCKRENDERER_H
#define MEGAMAN_BLOCKRENDERER_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <string>
#include <utility>
#include "Camera.h"

class TileRendererr;
typedef std::map<int, TileRendererr *> TileRenderers2;
typedef std::pair<int, int> AdjustedPos;
enum TileRendererType {
    BLOCK_R,
    STAIRS_R,
    PELLET_R
};

class TileRendererr {
public:
    TileRendererr(SDL2pp::Renderer *renderer, SDL2pp::Texture *sprites,
                      Camera &camera, float pos_x, float pos_y);
    void update(float pos_x, float pos_y);
    virtual void render() = 0;
    virtual ~TileRendererr() { }

protected:
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *sprites;
    Camera &camera;
    float pos_x;
    float pos_y;
};

class BlockRenderer : public TileRendererr {
public:
    using TileRendererr::TileRendererr;
    void render();
};

class StairsRenderer : public TileRendererr {
public:
    using TileRendererr::TileRendererr;
    void render();
};

class PelletRenderer : public TileRendererr {
public:
    using TileRendererr::TileRendererr;
    void render();
};

class TileRendererFactory {
public:
    TileRendererFactory(SDL2pp::Renderer *renderer, Camera &camera);
    TileRendererr* build_tile_renderer(std::string tile_type, float pos_x,
                                       float pos_y);
    virtual ~TileRendererFactory() {}
private:
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *sprites;
    Camera &camera;
    std::map<std::string, TileRendererType> tile_renderers;
};

#endif //MEGAMAN_BLOCKRENDERER_H
