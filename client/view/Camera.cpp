#include "Camera.h"

Camera::Camera(SDL2pp::Renderer *renderer) : renderer(renderer), offset_x(0),
                                             offset_y(0) { }

AdjustedPos Camera::adjust_position(float x, float y) {
    int adj_x = (int) x*50 - offset_x;
    int adj_y = renderer->GetOutputHeight() - (int) (y + 1)*50 + offset_y;
    return AdjustedPos(adj_x, adj_y);
}
Camera::~Camera() {}
