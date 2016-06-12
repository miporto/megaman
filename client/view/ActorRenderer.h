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
enum ActorRendererType {
    MET_R,
    BUMBY_R,
    SNIPER_R,
    JSNIPER_R,
    MEGAMAN_R,
    BOMBMAN_R
};

class ActorRenderer {
public:
    ActorRenderer(SDL2pp::Renderer *renderer, SDL2pp::Texture *sprites,
                       Camera &camera, float pos_x, float pos_y);
    void update(float pos_x, float pos_y, int dir_x, int dir_y);
    float get_x();
    float get_y();
    virtual void render() = 0;
    virtual ~ActorRenderer() { }

protected:
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *sprites;
    Camera &camera;
    float pos_x;
    float pos_y;
    int dir_x;
    int dir_y;
};

class MetRenderer : public ActorRenderer {
public:
    using ActorRenderer::ActorRenderer;
    void render();
};

class BumbyRenderer : public ActorRenderer {
public:
    using ActorRenderer::ActorRenderer;
    void render();
};

class SniperRenderer : public ActorRenderer {
public:
    using ActorRenderer::ActorRenderer;
    void render();
};

class JumpingSniperRenderer : public ActorRenderer {
public:
    using ActorRenderer::ActorRenderer;
    void render();
};

class MegaManRenderer : public ActorRenderer {
public:
    using ActorRenderer::ActorRenderer;
    void render();
};

class BombManRenderer : public ActorRenderer {
public:
    using ActorRenderer::ActorRenderer;
    void render();
};

class ActorRendererFactory {
public:
    ActorRendererFactory(SDL2pp::Renderer *renderer, Camera &camera);
    ActorRenderer* build_actor_renderer(std::string tile_type, float pos_x,
                                         float pos_y);
    virtual ~ActorRendererFactory() {}
private:
    SDL2pp::Renderer *renderer;
    Camera &camera;
    SDL2pp::Texture *meg_sprites;
    SDL2pp::Texture *enemy_sprites;
    SDL2pp::Texture *bomb_man_sprites;
    std::map<std::string, ActorRendererType> actor_renderers;
};

#endif //MEGAMAN_METRENDERER_H
