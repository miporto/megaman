#include <map>
#include <string>
#include <SDL2pp/SDL2pp.hh>
#include <vector>

#include "client/TickInfoParser.h"
#include "TileRenderer.h"
#include "StageRenderer.h"

StageRenderer::StageRenderer(SDL2pp::Renderer *renderer,
                             const std::string &stage_info) :
        renderer(renderer), tile_factory(renderer) {
    background = new SDL2pp::Texture(*renderer, "resources/background.png");
    TickInfoParser parser(stage_info);
    ActorRendererFactory actor_factory(renderer);


    std::vector<std::string> actors = {"MegaMan", "Met"};
    objects = {"Block", "Stairs"};
    NewTickParserInfo parsed_info = parser.get_new_parsed_tick_info();
    for (auto const &it: parsed_info) {
        std::string type = it.first;
        StatusInfo elements_info = it.second;
        for (auto const &it2: elements_info) {
            std::map<std::string, std::string> element_info = it2.second;
            float x = stof(element_info["x"]);
            float y = stof(element_info["y"]);
            AdjustedPos adjusted_pos = adjust_position(x, y);
//            if (element_info.count("dir_x") != 0 && element_info.count
//                    ("dir_y") != 0)
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
        a_renderer->update(x, y, 0, 0);
    } else {
        if (std::find(objects.begin(), objects.end(), name) != objects.end()) {
            tile_renderers[id] = tile_factory.build_tile_renderer(
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
        throw "ERROR: Non-existing id sent";
    }
}
//StageRenderer::StageRenderer(SDL2pp::Renderer *renderer,
//                             StageParserInfo& stage_info) :
//        renderer(renderer), stage_info(stage_info), tiles(renderer),
//        actors(renderer) {
//    background = new SDL2pp::Texture(*renderer, "resources/background.png");
//}
//
//void StageRenderer::update(const std::string &info) {
//    json json_info = json::parse(info);
//    for (json::iterator it = json_info.begin(); it != json_info.end(); ++it) {
//        std::string element = it.key();
//        std::vector<std::map<std::string, std::string>> elements = it.value();
//        std::cout << element << std::endl;
//    }
//}
//void StageRenderer::render_stage() {
//    TileRenderers tile_renderers = tiles.get_renderers();
//    for (auto const &iterator: stage_info) {
//        std::string tile_type = iterator.first;
//        // TODO: add a meaningfull exception if the tile doesnt exists
//        if (tile_renderers.count(tile_type) == 0) continue;
//        StageParserPositions positions = iterator.second;
//        for (size_t i = 0; i < positions.size(); ++i){
//            (tiles.*(tile_renderers[tile_type]))(positions[i][0],
//                                                 positions[i][1]);
//        }
//    }
//    render_spawn_actors();
//}
//void StageRenderer::render_spawn_actors() {
//    ActorRenderers actor_renderers = actors.get_renderers();
//    for (auto const &iterator: stage_info) {
//        std::string tile_type = iterator.first;
//        // TODO: add a meaningfull exception if the tile doesnt exists
//        if (actor_renderers.count(tile_type) == 0) continue;
//        StageParserPositions positions = iterator.second;
//        for (size_t i = 0; i < positions.size(); ++i){
//            (actors.*(actor_renderers[tile_type]))(positions[i][0],
//                                                 positions[i][1], 0, 0);
//        }
//        auto item = stage_info.find(tile_type);
//        stage_info.erase(item);
//    }
//}
//void StageRenderer::render_actors(const std::string& s_tick_info) {
//    TickInfoParser tick_parser(s_tick_info);
//    TickParserInfo parsed_tick_info = tick_parser.get_parsed_tick_info();
//    ActorRenderers actor_renderers = actors.get_renderers();
//    for (auto const &iterator: parsed_tick_info) {
//        std::string actor_type = iterator.first;
//        if (actor_renderers.count(actor_type) == 0) continue;
//        Coordinates coordinates = iterator.second;
//        for (size_t i = 0; i < coordinates.size(); ++i) {
//            (actors.*(actor_renderers[actor_type]))(coordinates[i][0],
//                                                 coordinates[i][1], 0, 0);
//        }
//    }
//}

void StageRenderer::render(const std::string &s_tick_info) {
    renderer->Copy(*background);
//    render_stage();
//    render_actors(s_tick_info);
}

StageRenderer::~StageRenderer() {
    delete background;
}
