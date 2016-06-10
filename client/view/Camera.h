#ifndef MEGAMAN_CAMERA_H
#define MEGAMAN_CAMERA_H


#include <extern/libSDL2pp/SDL2pp/Renderer.hh>

class Camera {
public:
    explicit Camera(SDL2pp::Renderer *renderer);
    ~Camera();
private:
    SDL2pp::Renderer *renderer;
    int offset_x;
    int offset_y;
};


#endif //MEGAMAN_CAMERA_H
