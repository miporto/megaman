#include "Camera.h"

Camera::Camera(SDL2pp::Renderer *renderer) : renderer(renderer), offset_x(0),
                                             offset_y(0) { }

AdjustedPos Camera::adjust_position(float x, float y) {
    int adj_x = (int) x*50 - offset_x;
    int adj_y = renderer->GetOutputHeight() - (int) (y + 1)*50 + offset_y;
    return AdjustedPos(adj_x, adj_y);
}

AdjustedSize Camera::adjust_size(int x, int y) {
    int adj_x = x * (renderer->GetOutputWidth() / 100);
    int adj_y = y * (renderer->GetOutputHeight() / 100);
    return AdjustedSize(adj_x, adj_y);
}
void Camera::add_megaman(int id, MegaManRenderer *megaman) {
    megs[id] = megaman;
}

void Camera::calculate_baricenter() {
    // TODO
//    MegaManRenderer *meg = megs[0];
//    float max_x = meg->get_x();
}
Camera::~Camera() {}
