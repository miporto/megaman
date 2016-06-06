#include <string>
#include <SDL2pp/SDL2pp.hh>

#include "TileRenderer.h"
#include "common/StageParser.h"
#include "StageRenderer.h"

StageRenderer::StageRenderer(SDL2pp::Renderer *renderer,
                             const StageParserInfo& stage_info) :
        renderer(renderer), stage_info(stage_info), tiles(renderer),
        met(renderer) {
    background = new SDL2pp::Texture(*renderer, "resources/background.png");
}

void StageRenderer::render() {
    renderer->Copy(*background);
    tile_renderers_t tile_renderers = tiles.get_renderers();

    // Render stage
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
//    (tiles.*(tile_renderers["block"]))(0, renderer->GetOutputHeight() - 40);
//    (tiles.*(tile_renderers["block"]))(50, renderer->GetOutputHeight() - 40);
//    (tiles.*(tile_renderers["block"]))(100, renderer->GetOutputHeight() - 40);
//    (tiles.*(tile_renderers["stairs"]))(0, renderer->GetOutputHeight() - 90);
//    tiles.render(0, renderer->GetOutputHeight() - 50);
//    tiles.render(50, renderer->GetOutputHeight() - 50);
//    tiles.render(100, renderer->GetOutputHeight() - 50);

    // Render actors (players, enemies, proyectiles)
    met.render(100, renderer->GetOutputHeight() - 100, 0);
}

StageRenderer::~StageRenderer() {
    delete background;
}
