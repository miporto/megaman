#include <map>
#include <string>
#include <SDL2pp/SDL2pp.hh>
#include <vector>

#include "client/TickInfoParser.h"
#include "TileRenderer.h"
#include "StageRenderer.h"

StageRenderer::StageRenderer(SDL2pp::Renderer *renderer,
                             const std::string &stage_info) :
        renderer(renderer) {
    background = new SDL2pp::Texture(*renderer, "resources/background.png");
    TickInfoParser parser(stage_info);
    TileRendererFactory tile_factory(renderer);
    ActorRendererFactory actor_factory(renderer);


    NewTickParserInfo parsed_info = parser.get_new_parsed_tick_info();
    for (auto const &it: parsed_info) {
        std::string type = it.first;
        StatusInfo elements_info = it.second;
        for (auto const &it2: elements_info) {
            std::map<std::string, std::string> element_info = it2.second;
            float x = stof(element_info["x"]);
            float y = stof(element_info["y"]);
            if (element_info.count("dir_x") != 0 && element_info.count
                    ("dir_y") != 0) {
                actor_renderers[it2.first] = actor_factory
                        .build_actor_renderer(type, x, y);
            } else {
                tile_renderers[it2.first] = tile_factory.build_tile_renderer(
                        type, x, y);
            }
        }
    }
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
