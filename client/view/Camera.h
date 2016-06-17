#ifndef MEGAMAN_CAMERA_H
#define MEGAMAN_CAMERA_H

#include <extern/libSDL2pp/SDL2pp/Renderer.hh>
#include <utility>
#include <map>

#include "ActorRenderer.h"
#include "MegaManRenderer.h"

class MegaManRenderer;
typedef std::pair<int, int> AdjustedPos;
typedef std::pair<int, int> AdjustedSize;
class Camera {
public:
    explicit Camera(SDL2pp::Renderer *renderer);
    AdjustedPos adjust_position(float x, float y);
    AdjustedPos adjust_proyectile_position(float x, float y);
    int adjust_size();
    void add_megaman(int id, MMegaManRenderer* megaman);
    void delete_megaman(int id); //Deletes the megaman from the array, not
    // the object itself
    ~Camera();
private:
    void calculate_baricenter();
    SDL2pp::Renderer *renderer;
    float offset_x;
    float offset_y;
    std::map<int, MMegaManRenderer*> megs;
};


#endif //MEGAMAN_CAMERA_H
