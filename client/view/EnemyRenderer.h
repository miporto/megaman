#ifndef MEGAMAN_METRENDERER_H
#define MEGAMAN_METRENDERER_H

#include <map>
#include <SDL2pp/SDL2pp.hh>
#include <string>
#include <vector>
#include <utility>
#include "Camera.h"

class Camera;
typedef std::pair<int, int> AdjustedPos;
enum EnemyRendererType {
    MET_R,
    BUMBY_R,
    SNIPER_R,
    JSNIPER_R,
    MEGAMAN_R,
    BOMBMAN_R
};

class EnemyRenderer {
public:
    EnemyRenderer(SDL2pp::Renderer *renderer, SDL2pp::Texture *sprites,
                       Camera &camera, float pos_x, float pos_y);
    void update(float pos_x, float pos_y, char covered);
    float get_x();
    float get_y();
    virtual void render() = 0;
    virtual ~EnemyRenderer() { }

protected:
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *sprites;
    Camera &camera;
    float pos_x;
    float pos_y;
    char covered;
};

class MetRenderer : public EnemyRenderer {
public:
    using EnemyRenderer::EnemyRenderer;
    void render();
};

class BumbyRenderer : public EnemyRenderer {
public:
    using EnemyRenderer::EnemyRenderer;
    void render();
};

class SniperRenderer : public EnemyRenderer {
public:
    using EnemyRenderer::EnemyRenderer;
    void render();
};

class JumpingSniperRenderer : public EnemyRenderer {
public:
    using EnemyRenderer::EnemyRenderer;
    void render();
};

class EnemyRendererFactory {
public:
    EnemyRendererFactory(SDL2pp::Renderer *renderer, Camera &camera);
    EnemyRenderer* build_actor_renderer(std::string tile_type, float pos_x,
                                         float pos_y);
    virtual ~EnemyRendererFactory() {}
private:
    SDL2pp::Renderer *renderer;
    Camera &camera;
    SDL2pp::Texture *enemy_sprites;
    std::map<std::string, EnemyRendererType> actor_renderers;
};

#endif //MEGAMAN_METRENDERER_H
