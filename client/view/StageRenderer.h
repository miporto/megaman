#ifndef MEGAMAN_STAGERENDERER_H
#define MEGAMAN_STAGERENDERER_H

#include <map>
#include <SDL2pp/SDL2pp.hh>
#include <string>
#include <vector>

#include "server/model/GameObjectParser.h"
#include "client/communication/ClientCommunicator.h"
#include "TileRenderer.h"
#include "ActorRenderer.h"
#include "Camera.h"
#include "BossRenderer.h"
#include "MegaManRenderer.h"

class TileRenderer;

class StageRenderer {
public:
    StageRenderer(SDL2pp::Renderer *renderer, std::string &stage_info);
    void render();
//    void update(const std::string &name, const std::string &update_info);
    void new_update(const std::string &name, UpdateInfo &update_info);
    void delete_renderer(int id);
    void render_boss_chamber(std::string &info);
    void render_end_game_msg();
    bool game_ended();
    bool game_won();
    ~StageRenderer();

private:
    void render_ready_msg();
    void create_renderers(std::string &info);
    void delete_all_renderers();
    SDL2pp::Renderer *renderer;
    SDL2pp::Texture *background;
    Camera camera;
    std::map<int, TileRenderer*> tile_renderers;
    std::map<int, ActorRenderer*> actor_renderers;
    std::map<int, BossRenderer*> boss_renderers;
    std::map<int, MegaManRenderer*> meg_renderers;
    std::vector<std::string> actors;
    std::vector<std::string> bosses;
    std::vector<std::string> objects;
    TileRendererFactory tile_factory;
    ActorRendererFactory actor_factory;
    BossRendererFactory boss_factory;
    bool on_boss_chamber = false;
};


#endif //MEGAMAN_STAGERENDERER_H
