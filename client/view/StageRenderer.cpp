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
    actors = {MET, BUMBY, SNIPER, JSNIPER};
    bosses = {BOMBMAN, MAGNETMAN, SPARKMAN, RINGMAN, FIREMAN};
    objects = {BLOCK, STAIRS, CLIFF, SPIKE, DOOR, PELLET, BOMB, FIRE, MAGNET, RING,
               SPARK, PLASMA};
    create_renderers(stage_info);
}

void StageRenderer::render() {
    renderer->Copy(*background);

    // Render tiles
    TileRenderer *tile_renderer;
    for (auto const &it: tile_renderers) {
        tile_renderer = it.second;
        tile_renderer->render();
    }

    // Render mega mans
    MegaManRenderer *meg_renderer;
    for (auto const &it: meg_renderers) {
        meg_renderer = it.second;
        meg_renderer->render();
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

void StageRenderer::new_update(const std::string &name,
                               UpdateInfo &update_info) {
    int id = (int) update_info["id"];
    float x = update_info["x"];
    float y = update_info["y"];
    if (tile_renderers.count(id) != 0) {
        TileRenderer *t_renderer = tile_renderers[id];
        t_renderer->update(x,  y);
    } else if (actor_renderers.count(id) != 0) {
        char covered = (char) update_info["covered"];
        ActorRenderer *a_renderer = actor_renderers[id];
        a_renderer->update(x, y, covered);
    } else if (meg_renderers.count(id) != 0){
        MegaManRenderer *m_renderer = meg_renderers[id];
        int dir_x = (int) update_info["dir_x"];
        int dir_y = (int) update_info["dir_y"];
        float energy =  update_info["energy"];
        m_renderer->update(x, y, dir_x,  dir_y, energy);
    } else if (boss_renderers.count(id) != 0) {
        int dir_x = (int) update_info["dir_x"];
        int dir_y = (int) update_info["dir_y"];
        int energy = (int) update_info["energy"];
        BossRenderer *b_renderer = boss_renderers[id];
        b_renderer->update(x, y, dir_x, dir_y, energy);
    } else {
        if (std::find(objects.begin(), objects.end(), name) != objects.end()) {
            tile_renderers[id] = tile_factory.build_tile_renderer(
                    name, x, y);
        } else if (std::find(actors.begin(), actors.end(), name) !=
                   actors.end()){
            actor_renderers[id] = actor_factory.build_actor_renderer(name, x,
                                                                     y);
        } else if (std::find(bosses.begin(), bosses.end(), name) !=
                   bosses.end()) {
            int energy = (int) update_info["energy"];
            boss_renderers[id] = boss_factory.build_boss_renderer(name, x, y,
                                                                  energy);
        }
    }
}

void StageRenderer::delete_renderer(int id) {
    if (tile_renderers.count(id) != 0) {
        TileRenderer *t_renderer = tile_renderers[id];
        tile_renderers.erase(id);
        delete t_renderer;
    } else if (actor_renderers.count(id) != 0) {
        ActorRenderer *a_renderer = actor_renderers[id];
        actor_renderers.erase(id);
        delete a_renderer;
    } else if (meg_renderers.count(id) != 0) {
        MegaManRenderer *m_renderer = meg_renderers[id];
        meg_renderers.erase(id);
        camera.delete_megaman(id);
        delete m_renderer;
    } else if (boss_renderers.count(id) != 0) {
        BossRenderer *b_renderer = boss_renderers[id];
        boss_renderers.erase(id);
        delete b_renderer;
    }
}

bool StageRenderer::game_ended() {
    if (on_boss_chamber) {
        return boss_renderers.size() == 0 || meg_renderers.size() == 0;
    }
    return meg_renderers.size() == 0;
}

bool StageRenderer::game_won() {
    return on_boss_chamber && boss_renderers.size() == 0 &&
            meg_renderers.size() > 0;
}

void StageRenderer::render_ready_msg() {
    SDL2pp::SDLTTF ttf;
    SDL2pp::Font font("resources/megaman_2.ttf", 48);
    std::string text = "READY?";
    SDL2pp::Texture text_sprite(
            *renderer,
            font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255}));
    int text_w= text_sprite.GetWidth();
    int text_h = text_sprite.GetHeight();
    int hcenter = renderer->GetOutputWidth() / 2;
    int vcenter = renderer->GetOutputHeight() / 2;
    renderer->Copy(text_sprite, SDL2pp::NullOpt, SDL2pp::Rect(hcenter - text_w/2,
                                                              vcenter - text_h/2,
                                                              text_w, text_h));
}

void StageRenderer::render_end_game_msg() {
    SDL2pp::SDLTTF ttf;
    SDL2pp::Font font("resources/megaman_2.ttf", 48);
    std::string text;
    if (meg_renderers.size() == 0) {
        text = "GAME OVER";
    } else {
        text = "YOU WON!!";
    }
    SDL2pp::Texture text_sprite(
            *renderer,
            font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255}));
    int text_w= text_sprite.GetWidth();
    int text_h = text_sprite.GetHeight();
    int hcenter = renderer->GetOutputWidth() / 2;
    int vcenter = renderer->GetOutputHeight() / 2;
    renderer->Copy(text_sprite, SDL2pp::NullOpt, SDL2pp::Rect(hcenter - text_w/2,
                                                              vcenter - text_h/2,
                                                              text_w, text_h));
}

void StageRenderer::render_boss_chamber(std::string &info) {
    on_boss_chamber = true;
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
            } else if (type.compare(MEGAMAN) == 0) {
                int energy = stoi(element_info["energy"]);
                std::string name = element_info["name"];
                MegaManRenderer *mega_man_renderer = new MegaManRenderer(
                        renderer, camera, x, y, energy, name);
                meg_renderers[id] = mega_man_renderer;
                camera.add_megaman(id, mega_man_renderer);
            } else if (std::find(objects.begin(), objects.end(), type) !=
                    objects.end()){
                tile_renderers[it2.first] = tile_factory.build_tile_renderer(
                        type, x, y);
            } else if (std::find(bosses.begin(), bosses.end(), type) !=
                    bosses.end()) {
                int energy = stoi(element_info["energy"]);
                boss_renderers[id] = boss_factory.build_boss_renderer(type,
                                                                      x, y,
                                                                      energy);
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

    for (auto const &it : meg_renderers) {
        camera.delete_megaman(it.first);
        MegaManRenderer *m_renderer = it.second;
        delete m_renderer;
    }
    meg_renderers.clear();
}

StageRenderer::~StageRenderer() {
    delete background;
    delete_all_renderers();
    for (auto const &it : boss_renderers) {
        BossRenderer *b_renderer = it.second;
        delete b_renderer;
    }
    boss_renderers.clear();
}

//void StageRenderer::update(const std::string &name,
//                           const std::string &update_info) {
//    std::map<std::string, std::string> parsed_update =
//            TickInfoParser::parse_update(update_info);
//    int id = stoi(parsed_update["id"]);
//    float x = std::stof(parsed_update["x"]);
//    float y = std::stof(parsed_update["y"]);
//    if (tile_renderers.count(id) != 0) {
//        TileRenderer *t_renderer = tile_renderers[id];
//        t_renderer->update(x,  y);
//    } else if (actor_renderers.count(id) != 0) {
//        ActorRenderer *a_renderer = actor_renderers[id];
//        a_renderer->update(x, y, 0, 0);
//    } else {
//        if (std::find(objects.begin(), objects.end(), name) != objects.end()) {
//            tile_renderers[id] = tile_factory.build_tile_renderer(
//                    name, x, y);
//        } else if (std::find(actors.begin(), actors.end(), name) !=
//                   actors.end()){
//            actor_renderers[id] = actor_factory.build_actor_renderer(name, x,
//                                                                     y);
//        }
//    }
//}
