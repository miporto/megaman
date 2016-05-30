#include <vector>

#include "GameObject.h"

GameObject::GameObject(const std::vector<int>& position)
        : position(position) {}

GameObject::GameObject(const int x, const int y, const int direction)
        : position(x, y, direction) {}

void GameObject::set_body(b2Body* body) {
    this->body = body;
}

std::vector<int> GameObject::get_position() {
    return this->position.get_position();
}

GameObject::~GameObject() {}
