#include <algorithm>

#include "Camera.h"

Camera::Camera(SDL2pp::Renderer *renderer) : renderer(renderer), offset_x(0),
                                             offset_y(0) { }

AdjustedPos Camera::adjust_position(float x, float y) {
    int size = adjust_size();
    int adj_x = (int) x*size - offset_x;
    int adj_y = renderer->GetOutputHeight() - (int) (y + 1)*size + offset_y;
    return AdjustedPos(adj_x, adj_y);
}

int Camera::adjust_size() {
    int width = renderer->GetOutputWidth();
    int height = renderer->GetOutputHeight();
    return std::min(width, height) / 10;
}

void Camera::add_megaman(int id, MegaManRenderer *megaman) {
    megs[id] = megaman;
}

void Camera::delete_megaman(int id) {
    megs.erase(id);
}
void Camera::calculate_baricenter() {
    // TODO
    MegaManRenderer *meg = megs[0];
    float max_x = meg->get_x();
    float max_y = meg->get_y();
    for (auto const &it: megs) {
        float act_x = it.second->get_x();
        if (act_x >= max_x) max_x = act_x;
        float act_y = it.second->get_y();
        if (act_x >= max_y) max_y = act_y;
    }
}
Camera::~Camera() {}
