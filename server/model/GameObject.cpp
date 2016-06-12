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
    if (x < (others_x + other->get_side()) && others_x < (x + this->side)
        && y < (others_y + other->get_side()) && others_y < (y + this->side))
        return true;
    return false;
}

std::vector<float> GameObject::get_position() {
    return this->position.get_position();
}

bool GameObject::it_moved() { return false; }

bool GameObject::is_enemy() { return false; }

bool GameObject::is_megaman() { return false; }

GameObject::~GameObject() {}
