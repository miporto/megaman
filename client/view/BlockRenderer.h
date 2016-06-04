#ifndef MEGAMAN_BLOCKRENDERER_H
#define MEGAMAN_BLOCKRENDERER_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <string>

class BlockRenderer;
typedef void (BlockRenderer::*trenderer_method_t)(int,int);
typedef std::map<std::string, trenderer_method_t> tile_renderers_t;

class BlockRenderer {
public:
    explicit BlockRenderer(SDL2pp::Renderer* renderer);
    tile_renderers_t get_renderers();
    void render(int dest_x, int dest_y);
    virtual ~BlockRenderer();
private:
    tile_renderers_t renderers;
    SDL2pp::Renderer* renderer;
    SDL2pp::Texture* sprites;
};


#endif //MEGAMAN_BLOCKRENDERER_H
