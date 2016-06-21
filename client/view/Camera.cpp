#include <algorithm>

#include "Camera.h"

Camera::Camera(SDL2pp::Renderer *renderer) : renderer(renderer), offset_x(0),
                                             offset_y(0), x(0), y(0) { }

AdjustedPos Camera::adjust_position(float x, float y) {
    calculate_baricenter();
    int size = adjust_size();
    int adj_x = (int) ((x + offset_x) * size);
    int adj_y = (int) (renderer->GetOutputHeight() - (y + 1 + offset_y)*size);
    return AdjustedPos(adj_x, adj_y);
}

AdjustedPos Camera::adjust_enemy_meg_position(float x, float y){
    calculate_baricenter();
    int size = (int) (adjust_size() * 0.85);
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

int Camera::adjust_enemy_size() {
    return (int) (adjust_size() * 0.75);
}

void Camera::add_megaman(int id, MegaManRenderer *megaman) {
    megs[id] = megaman;
}

void Camera::delete_megaman(int id) {
    megs.erase(id);
}
void Camera::calculate_baricenter() {
    if (megs.size() == 0) return;
    int size = adjust_size();
    float max_x;
    float min_x;
    float max_y;
    float min_y;
    bool setup = true;
    for (auto const &it: megs) {
        if (setup) {
            max_x = it.second->get_x();
            min_x = max_x;
            max_y = it.second->get_y();
            min_y = max_y;
            setup = false;
        }
        float act_x = it.second->get_x();
        float act_y = it.second->get_y();
        if (act_x > max_x) max_x = act_x;
        if (act_x < min_x) min_x = act_x;
        if (act_x > max_y) max_y = act_y;
        if (act_y < min_y) min_y = act_y;
    }

    int width = renderer->GetOutputWidth();
    int height = renderer->GetOutputHeight();
    float b_x = (max_x + min_x) / 2;
    float b_y = (max_y + min_y) / 2;
    if (b_x - x < 0) x = 0;
    if (b_x*size <  width * 0.25) {
        offset_x = 0;
    } else if ((b_x - x)*size > width * 0.75) {
        offset_x = -b_x;
        x = b_x;
    }

    if (b_y < height * 0.25) {
        offset_y = 0;
    } else if (b_y > width * 0.75) {
        offset_y = -b_y;
    }
//    if (b_x*size > width*0.75) {
//        std::cout << b_x << ", " << x << "Size: " << size << std::endl;
//        offset_x = -width/size;
//        x = b_x;
//    } else {
//        offset_x = 0;
//    }
//    if (b_y < 0) {
//        offset_y = 0;
//    } else if (b_y > height) {
//        offset_y = height;
//    } else {
//        offset_y = 0;
//    }
//    std::cout << offset_x << ", " << offset_y << std::endl;
}
Camera::~Camera() {}
