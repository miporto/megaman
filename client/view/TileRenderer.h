#ifndef MEGAMAN_BLOCKRENDERER_H
#define MEGAMAN_BLOCKRENDERER_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <string>

class TileRendererr;

typedef std::map<int, TileRendererr *> TileRenderers2;
enum TileRendererType {
    BLOCK_R,
    STAIRS_R,
};

class TileRendererr {
public:
    TileRendererr(SDL2pp::Renderer *renderer, SDL2pp::Texture *sprites,
                  float pos_x, float pos_y);

    void update(float pos_x, float pos_y);

    virtual void render() = 0;

    virtual ~TileRendererr() { }

protected:
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *sprites;
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
class TileRendererFactory {
public:
    explicit TileRendererFactory(SDL2pp::Renderer * renderer);
    TileRendererr* build_tile_renderer(std::string tile_type, float pos_x,
                                       float pos_y);
    virtual ~TileRendererFactory() {}
private:
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *sprites;
    std::map<std::string, TileRendererType> tile_renderers;
};



// Old stuff, deprecated --siempre quise usar esta palabra (?
class TileRenderer;

typedef void (TileRenderer::*trenderer_method_t)(int, int);

typedef std::map<std::string, trenderer_method_t> TileRenderers;

class TileRenderer {
public:
    explicit TileRenderer(SDL2pp::Renderer *renderer);

    TileRenderers get_renderers();

    void renderBlock(int dest_x, int dest_y);

    void renderStairs(int dest_x, int dest_y);

    virtual ~TileRenderer();

private:
    TileRenderers renderers;
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *sprites;
};


#endif //MEGAMAN_BLOCKRENDERER_H
