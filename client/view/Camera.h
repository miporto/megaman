#ifndef MEGAMAN_CAMERA_H
#define MEGAMAN_CAMERA_H

#include <extern/libSDL2pp/SDL2pp/Renderer.hh>
#include <utility>

typedef std::pair<int, int> AdjustedPos;
class Camera {
public:
    explicit Camera(SDL2pp::Renderer *renderer);
    AdjustedPos adjust_position(float x, float y);
    ~Camera();
private:
    SDL2pp::Renderer *renderer;
    int offset_x;
    int offset_y;
};


#endif //MEGAMAN_CAMERA_H
