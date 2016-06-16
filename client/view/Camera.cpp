#include <algorithm>

#include "Camera.h"

Camera::Camera(SDL2pp::Renderer *renderer) : renderer(renderer), offset_x(0),
                                             offset_y(0) { }

AdjustedPos Camera::adjust_position(float x, float y) {
    calculate_baricenter();
    int size = adjust_size();
    int adj_x = (int) ((x + offset_x) * size);
    int adj_y = (int) (renderer->GetOutputHeight() - (y + 1 + offset_y)*size);
    return AdjustedPos(adj_x, adj_y);
}

AdjustedPos Camera::adjust_proyectile_position(float x, float y) {
    calculate_baricenter();
    int size = adjust_size();
    int adj_x = (int) ((x + offset_x) * size);
    int adj_y = (int) (renderer->GetOutputHeight() - (y + offset_y) * size);
    return AdjustedPos(adj_x, adj_y);
}
int Camera::adjust_size() {
    int width = renderer->GetOutputWidth();
    int height = renderer->GetOutputHeight();
    return std::min(width, height) / 10;
}

void Camera::add_megaman(int id, MMegaManRenderer *megaman) {
    megs[id] = megaman;
}

void Camera::delete_megaman(int id) {
    megs.erase(id);
}
void Camera::calculate_baricenter() {
    // TODO: do not change offset when megs are on the map border
    float max_x = -1;
    float min_x = max_x;
    float max_y = -1;
    float min_y = max_y;
    for (auto const &it: megs) {
        float act_x = it.second->get_x();
        float act_y = it.second->get_y();
        if (act_x > max_x) max_x = act_x;
        if (act_x < min_x) min_x = act_x;
        if (act_x > max_y) max_y = act_y;
        if (act_y < min_y) min_y = act_y;
    }
    float b_x = (max_x + min_x) / 2;
    float b_y = (max_y + min_y) / 2;
    int width = renderer->GetOutputWidth();
    int height = renderer->GetOutputHeight();
    if (b_x <  width * 0.25) {
        offset_x = -b_x;
    } else if (b_x > width * 0.75) {
        offset_x = b_x;
    }
    if (b_y < height * 0.25) {
        offset_y = -b_y;
    } else if (b_y > width * 0.75) {
        offset_y = b_y;
    }
}
Camera::~Camera() {}
