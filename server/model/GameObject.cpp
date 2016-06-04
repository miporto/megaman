#include <vector>

#include "GameObject.h"

GameObject::GameObject(const std::vector<int>& position)
        : side(BODY_SIDE), position(position) {}

GameObject::GameObject(const int x, const int y)
        : side(BODY_SIDE), position(x, y) {}

int GameObject::get_side() {
    return this->side;
}

bool GameObject::collided_with(GameObject* other) {
    std::vector<int> vertex = this->get_position();
    int x = vertex[X_COORD_POS];
    int y = vertex[Y_COORD_POS];
    std::vector<int> others_vertex = other->get_position();
    int others_x = others_vertex[X_COORD_POS];
    int others_y = others_vertex[Y_COORD_POS];
    if (x < others_x && others_x < (x + this->side)
        && y < others_y && others_y < (y + this->side))
        return true;
    return false;
}

std::vector<int> GameObject::get_position() {
    return this->position.get_position();
}

GameObject::~GameObject() {}
