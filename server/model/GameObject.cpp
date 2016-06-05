#include <vector>

#include "GameObject.h"

GameObject::GameObject(const std::vector<float>& position)
        : side(BODY_SIDE), position(position) {}

GameObject::GameObject(const float x, const float y)
        : side(BODY_SIDE), position(x, y) {}

int GameObject::get_side() {
    return this->side;
}

bool GameObject::collided_with(GameObject* other) {
    std::vector<float> vertex = this->get_position();
    float x = vertex[X_COORD_POS];
    float y = vertex[Y_COORD_POS];
    std::vector<float> others_vertex = other->get_position();
    float others_x = others_vertex[X_COORD_POS];
    float others_y = others_vertex[Y_COORD_POS];
    if (x < others_x && others_x < (x + this->side)
        && y < others_y && others_y < (y + this->side))
        return true;
    return false;
}

std::vector<float> GameObject::get_position() {
    return this->position.get_position();
}

GameObject::~GameObject() {}
