#ifndef MEGAMAN_BOSSRENDERER_H
#define MEGAMAN_BOSSRENDERER_H

#include <map>
#include <string>

#include <extern/libSDL2pp/SDL2pp/Renderer.hh>
#include "Camera.h"

enum BossRendererType {
    BBOMBMAN_R,
    MAGNETMAN_R,
    SPARKMAN_R,
    RINGMAN_R,
    FIREMAN_R
};
class BossRenderer {
public:
    BossRenderer(SDL2pp::Renderer *renderer, SDL2pp::Texture *sprites,
                 Camera &camera, float pos_x, float pos_y, int energy);
    void update(float pos_x, float pos_y, int dir_x, int dir_y, int energy);
    virtual void render() = 0;
    virtual ~BossRenderer() {}
protected:
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *sprites;
    Camera &camera;
    float pos_x;
    float pos_y;
    int dir_x;
    int dir_y;
    int initial_energy;
    int actual_energy;
};

class BBombManRenderer : public BossRenderer {
public:
    using BossRenderer::BossRenderer;
    void render();
};

class MagnetManRenderer : public BossRenderer {
public:
    using BossRenderer::BossRenderer;
    void render();
};

class SparkManRenderer : public BossRenderer {
public:
    using BossRenderer::BossRenderer;
    void render();
};

class RingManRenderer : public BossRenderer {
public:
    using BossRenderer::BossRenderer;
    void render();
};

class FireManRenderer : public BossRenderer {
public:
    using BossRenderer::BossRenderer;
    void render();
};

class BossRendererFactory {
public:
    BossRendererFactory(SDL2pp::Renderer *renderer, Camera &camera);
    BossRenderer* build_boss_renderer(std::string tile_type, float pos_x,
                                       float pos_y, int energy);
    ~BossRendererFactory();
private:
    SDL2pp::Renderer *renderer;
    Camera &camera;
    SDL2pp::Texture *bomb_man_sprites;
    SDL2pp::Texture *magnet_man_sprites;
    SDL2pp::Texture *spark_man_sprites;
    SDL2pp::Texture *ring_man_sprites;
    SDL2pp::Texture *fire_man_sprites;
    std::map<std::string, BossRendererType > boss_renderers;
};
#endif //MEGAMAN_BOSSRENDERER_H
