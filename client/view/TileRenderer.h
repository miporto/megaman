#ifndef MEGAMAN_BLOCKRENDERER_H
#define MEGAMAN_BLOCKRENDERER_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <string>

class TileRenderer;
typedef void (TileRenderer::*trenderer_method_t)(int,int);
typedef std::map<std::string, trenderer_method_t> tile_renderers_t;

class TileRenderer {
public:
    explicit TileRenderer(SDL2pp::Renderer* renderer);
    tile_renderers_t get_renderers();
    void renderBlock(int dest_x, int dest_y);
    void renderStairs(int dest_x, int dest_y);
    virtual ~TileRenderer();
private:
    tile_renderers_t renderers;
    SDL2pp::Renderer* renderer;
    SDL2pp::Texture* sprites;
};


#endif //MEGAMAN_BLOCKRENDERER_H
