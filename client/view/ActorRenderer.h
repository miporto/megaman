#ifndef MEGAMAN_METRENDERER_H
#define MEGAMAN_METRENDERER_H

#include <map>
#include <SDL2pp/SDL2pp.hh>
#include <string>
#include <vector>

enum ActorRendererType {
    MET_R,
    MEGAMAN_R
};
class ActorRendererr {
public:
    ActorRendererr(SDL2pp::Renderer *renderer, SDL2pp::Texture *sprites,
                   int pos_x, int pos_y);

    void update(int pos_x, int pos_y, int dir_x, int dir_y);

    virtual void render() = 0;

    virtual ~ActorRendererr() { }

protected:
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *sprites;
    int pos_x;
    int pos_y;
    int dir_x;
    int dir_y;
};

class MetRenderer : public ActorRendererr {
public:
    using ActorRendererr::ActorRendererr;
    void render();
};

class MegaManRenderer : public ActorRendererr {
public:
    using ActorRendererr::ActorRendererr;
    void render();
};

class ActorRendererFactory {
public:
    explicit ActorRendererFactory(SDL2pp::Renderer * renderer);
    ActorRendererr* build_actor_renderer(std::string tile_type, int pos_x,
                                         int pos_y);
    virtual ~ActorRendererFactory() {}
private:
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *meg_sprites;
    SDL2pp::Texture *sprites;
    std::map<std::string, ActorRendererType> actor_renderers;
};

#endif //MEGAMAN_METRENDERER_H
