#ifndef MEGAMAN_STAGERENDERER_H
#define MEGAMAN_STAGERENDERER_H

#include <SDL2pp/SDL2pp.hh>


class StageRenderer {
public:
    explicit StageRenderer(SDL2pp::Renderer* renderer);
    void render();
    ~StageRenderer();
private:
    SDL2pp::Renderer* renderer;
    SDL2pp::Texture* background;
};


#endif //MEGAMAN_STAGERENDERER_H
