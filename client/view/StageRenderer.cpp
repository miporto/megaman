#include <string>
#include <SDL2pp/SDL2pp.hh>

#include "client/TickInfoParser.h"
#include "TileRenderer.h"
#include "common/StageParser.h"
#include "StageRenderer.h"

StageRenderer::StageRenderer(SDL2pp::Renderer *renderer,
                             StageParserInfo& stage_info) :
        renderer(renderer), stage_info(stage_info), tiles(renderer),
        actors(renderer) {
    background = new SDL2pp::Texture(*renderer, "resources/background.png");
}

void StageRenderer::render_stage() {
    tile_renderers_t tile_renderers = tiles.get_renderers();
    for (auto const &iterator: stage_info) {
        std::string tile_type = iterator.first;
        // TODO: add a meaningfull exception if the tile doesnt exists
        if (tile_renderers.count(tile_type) == 0) continue;
        StageParserPositions positions = iterator.second;
        for (size_t i = 0; i < positions.size(); ++i){
            (tiles.*(tile_renderers[tile_type]))(positions[i][0],
                                                 positions[i][1]);
        }
    }
    render_spawn_actors();
}
void StageRenderer::render_spawn_actors() {
    ActorRenderers actor_renderers = actors.get_renderers();
    for (auto const &iterator: stage_info) {
        std::string tile_type = iterator.first;
        // TODO: add a meaningfull exception if the tile doesnt exists
        if (actor_renderers.count(tile_type) == 0) continue;
        StageParserPositions positions = iterator.second;
        for (size_t i = 0; i < positions.size(); ++i){
            (actors.*(actor_renderers[tile_type]))(positions[i][0],
                                                 positions[i][1], 0, 0);
        }
        auto item = stage_info.find(tile_type);
        stage_info.erase(item);
    }
}
void StageRenderer::render_actors(const std::string& s_tick_info) {
    TickInfoParser tick_parser(s_tick_info);
    TickParserInfo parsed_tick_info = tick_parser.get_parsed_tick_info();
    ActorRenderers actor_renderers = actors.get_renderers();
    for (auto const &iterator: parsed_tick_info) {
        std::string actor_type = iterator.first;
        if (actor_renderers.count(actor_type) == 0) continue;
        Coordinates coordinates = iterator.second;
        for (size_t i = 0; i < coordinates.size(); ++i) {
            (actors.*(actor_renderers[actor_type]))(coordinates[i][0],
                                                 coordinates[i][1], 0, 0);
        }
    }
}

void StageRenderer::render(const std::string& s_tick_info) {
    renderer->Copy(*background);
    render_stage();
    render_actors(s_tick_info);
}

StageRenderer::~StageRenderer() {
    delete background;
}
