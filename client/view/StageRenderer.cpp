#include <map>
#include <string>
#include <SDL2pp/SDL2pp.hh>
#include <vector>

#include "client/TickInfoParser.h"
#include "TileRenderer.h"
#include "StageRenderer.h"

StageRenderer::StageRenderer(SDL2pp::Renderer *renderer,
                             const std::string &stage_info) :
        renderer(renderer), tile_factory(renderer), actor_factory(renderer) {
    background = new SDL2pp::Texture(*renderer, "resources/background.png");
    TickInfoParser parser(stage_info);
    actors = {"MegaMan", "Met"};
    objects = {"Block", "Stairs", "Pellet"};
    NewTickParserInfo parsed_info = parser.get_new_parsed_tick_info();
    for (auto const &it: parsed_info) {
        std::string type = it.first;
        StatusInfo elements_info = it.second;
        for (auto const &it2: elements_info) {
            std::map<std::string, std::string> element_info = it2.second;
            float x = stof(element_info["x"]);
            float y = stof(element_info["y"]);
            AdjustedPos adjusted_pos = adjust_position(x, y);
            if (std::find(actors.begin(), actors.end(), type) != actors.end()){
                actor_renderers[it2.first] = actor_factory
                        .build_actor_renderer(type, adjusted_pos.first,
                                              adjusted_pos.second);
            } else {
                tile_renderers[it2.first] = tile_factory.build_tile_renderer(
                        type, adjusted_pos.first, adjusted_pos.second);
            }
        }
    }
}

AdjustedPos StageRenderer::adjust_position(float x, float y) {
    AdjustedPos adjusted_pos;
    int adj_x = (int) x*50;
    int adj_y = renderer->GetOutputHeight() - (int) (y + 1)*50;
    adjusted_pos.first = adj_x;
    adjusted_pos.second = adj_y;
    return adjusted_pos;
}
void StageRenderer::render() {
    renderer->Copy(*background);
    TileRendererr *tile_renderer;
    for (auto const &it: tile_renderers) {
        tile_renderer = it.second;
        tile_renderer->render();
    }

    ActorRendererr *actor_renderer;
    for (auto const &it: actor_renderers) {
        actor_renderer = it.second;
        actor_renderer->render();
    }
}

void StageRenderer::update(const std::string &name,
                           const std::string &update_info) {
    std::map<std::string, std::string> parsed_update =
            TickInfoParser::parse_update(update_info);
    int id = stoi(parsed_update["id"]);
    float x = stof(parsed_update["x"]);
    float y = stof(parsed_update["y"]);
    AdjustedPos adjusted_pos = adjust_position(x, y);
    if (tile_renderers.count(id) != 0) {
        TileRendererr *t_renderer = tile_renderers[id];
        t_renderer->update(adjusted_pos.first,  adjusted_pos.second);
    } else if (actor_renderers.count(id) != 0) {
        ActorRendererr *a_renderer = actor_renderers[id];
        a_renderer->update(adjusted_pos.first, adjusted_pos.second, 0, 0);
    } else {
        if (std::find(objects.begin(), objects.end(), name) != objects.end()) {
            tile_renderers[id] = tile_factory.build_tile_renderer(
                    name, adjusted_pos.first, adjusted_pos.second);
        } else if (std::find(actors.begin(), actors.end(), name) !=
                actors.end()){
            actor_renderers[id] = actor_factory.build_actor_renderer(
                    name, adjusted_pos.first, adjusted_pos.second);
        }
    }
}
void StageRenderer::delete_renderer(int id) {
    if (tile_renderers.count(id) != 0) {
        tile_renderers.erase(id);
    } else if (actor_renderers.count(id != 0)) {
        actor_renderers.erase(id);
    } else {
        return;
        //throw "ERROR: Non-existing id sent";
    }
}

StageRenderer::~StageRenderer() {
    delete background;
}
