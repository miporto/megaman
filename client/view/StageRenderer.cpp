#include <map>
#include <string>
#include <SDL2pp/SDL2pp.hh>
#include <vector>

#include "client/TickInfoParser.h"
#include "TileRenderer.h"
#include "StageRenderer.h"
#include "StageElementsConstants.h"

StageRenderer::StageRenderer(SDL2pp::Renderer *renderer,
                             std::string &stage_info) : renderer(renderer),
                                                        camera(renderer),
                                                        tile_factory(renderer,
                                                                     camera),
                                                        actor_factory(renderer,
                                                                      camera),
                                                        boss_factory(renderer,
                                                                     camera) {
    background = new SDL2pp::Texture(*renderer, "resources/background.png");
    actors = {"MegaMan", "Met", "Bumby", "Sniper", "JumpingSniper"};
    bosses = {BOMBMAN, MAGNETMAN, SPARKMAN, RINGMAN, FIREMAN};
    objects = {"Block", "Stairs", "Spike", "Plasma", "Pellet", "Door"};

    TickInfoParser parser(stage_info);
    TickParserInfo parsed_info = parser.get_parsed_tick_info();
    for (auto const &it: parsed_info) {
        std::string type = it.first;
        StatusInfo elements_info = it.second;
        for (auto const &it2: elements_info) {
            std::map<std::string, std::string> element_info = it2.second;
            float x = stof(element_info["x"]);
            float y = stof(element_info["y"]);
            if (std::find(actors.begin(), actors.end(), type) != actors.end()){
                int id = it2.first;
                actor_renderers[id] = actor_factory
                        .build_actor_renderer(type, x, y);
                if (type.compare("MegaMan") == 0) {
                    megamans.push_back(id);
                    camera.add_megaman(id, (MegaManRenderer*)
                            actor_renderers[id]);
                }
            } else {
                tile_renderers[it2.first] = tile_factory.build_tile_renderer(
                        type, x, y);
            }
        }
    }
}

void StageRenderer::render() {
    renderer->Copy(*background);

    // Render tiles
    TileRenderer *tile_renderer;
    for (auto const &it: tile_renderers) {
        tile_renderer = it.second;
        tile_renderer->render();
    }

    // Render enemies
    ActorRenderer *actor_renderer;
    for (auto const &it: actor_renderers) {
        actor_renderer = it.second;
        actor_renderer->render();
    }

    // Render bosses
    BossRenderer *boss_renderer;
    for (auto const &it: boss_renderers) {
        boss_renderer = it.second;
        boss_renderer->render();
    }
}

void StageRenderer::update(const std::string &name,
                           const std::string &update_info) {
    std::map<std::string, std::string> parsed_update =
            TickInfoParser::parse_update(update_info);
    int id = stoi(parsed_update["id"]);
    float x = std::stof(parsed_update["x"]);
    float y = std::stof(parsed_update["y"]);
    if (tile_renderers.count(id) != 0) {
        TileRenderer *t_renderer = tile_renderers[id];
        t_renderer->update(x,  y);
    } else if (actor_renderers.count(id) != 0) {
        ActorRenderer *a_renderer = actor_renderers[id];
        a_renderer->update(x, y, 0, 0);
    } else {
        if (std::find(objects.begin(), objects.end(), name) != objects.end()) {
            tile_renderers[id] = tile_factory.build_tile_renderer(
                    name, x, y);
        } else if (std::find(actors.begin(), actors.end(), name) !=
                actors.end()){
            actor_renderers[id] = actor_factory.build_actor_renderer(name, x,
                                                                     y);
        }
    }
}

void StageRenderer::new_update(const std::string &name,
                               FloatUpdatePkt &update_info) {
    int id = (int) update_info["id"];
    float x = update_info["x"];
    float y = update_info["y"];
    if (tile_renderers.count(id) != 0) {
        TileRenderer *t_renderer = tile_renderers[id];
        t_renderer->update(x,  y);
    } else if (actor_renderers.count(id) != 0) {
        ActorRenderer *a_renderer = actor_renderers[id];
        a_renderer->update(x, y, 0, 0);
    } else {
        if (std::find(objects.begin(), objects.end(), name) != objects.end()) {
            tile_renderers[id] = tile_factory.build_tile_renderer(
                    name, x, y);
        } else if (std::find(actors.begin(), actors.end(), name) !=
                   actors.end()){
            actor_renderers[id] = actor_factory.build_actor_renderer(name, x,
                                                                     y);
        }
    }
}
void StageRenderer::delete_renderer(int id) {
    // TODO: check with camera, cause  if its a meg it has to delete it too
    if (tile_renderers.count(id) != 0) {
        tile_renderers.erase(id);
    } else if (actor_renderers.count(id) != 0) {
        actor_renderers.erase(id);
        auto pos = std::find(megamans.begin(), megamans.end(), id);
        if (pos != megamans.end()) {
            camera.delete_megaman(id);
            megamans.erase(pos);
        }
    } else {
        return;
        //throw "ERROR: Non-existing id sent";
    }
}

bool StageRenderer::are_megamans_alive() {
    return megamans.size() > 0;
}

void StageRenderer::render_boss_chamber(std::string &info) {
    delete_all_renderers();
    create_renderers(info);
}
void StageRenderer::create_renderers(std::string &info) {
    TickInfoParser parser(info);
    TickParserInfo parsed_info = parser.get_parsed_tick_info();
    for (auto const &it: parsed_info) {
        std::string type = it.first;
        StatusInfo elements_info = it.second;
        for (auto const &it2: elements_info) {
            std::map<std::string, std::string> element_info = it2.second;
            float x = stof(element_info["x"]);
            float y = stof(element_info["y"]);
            int id = it2.first;
            if (std::find(actors.begin(), actors.end(), type) != actors.end()){
                actor_renderers[id] = actor_factory
                        .build_actor_renderer(type, x, y);
                if (type.compare("MegaMan") == 0) {
                    megamans.push_back(id);
                    camera.add_megaman(id, (MegaManRenderer*)
                            actor_renderers[id]);
                }
            } else if (std::find(objects.begin(), objects.end(), type) !=
                    objects.end()){
                tile_renderers[it2.first] = tile_factory.build_tile_renderer(
                        type, x, y);
            } else if (std::find(bosses.begin(), bosses.end(), type) !=
                    bosses.end()) {
                // TODO: put actual energy.
                boss_renderers[id] = boss_factory.build_boss_renderer(type,
                                                                      x, y, 30);
            }
        }
    }
}

void StageRenderer::delete_all_renderers(){
    for (auto const &it : tile_renderers) {
        TileRenderer *t_renderer = it.second;
        delete t_renderer;
    }
    tile_renderers.clear();
    for (auto const &it : actor_renderers) {
        camera.delete_megaman(it.first);
        ActorRenderer *a_renderer = it.second;
        delete a_renderer;
    }
    actor_renderers.clear();
    megamans.clear();
}

StageRenderer::~StageRenderer() {
    delete background;
    for (auto const &it : tile_renderers) {
        TileRenderer *t_renderer = it.second;
        delete t_renderer;
    }
    tile_renderers.clear();
    for (auto const &it : actor_renderers) {
        ActorRenderer *a_renderer = it.second;
        delete a_renderer;
    }
    actor_renderers.clear();
}
