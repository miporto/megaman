#include <vector>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Box2D.h>

#include "GameObject.h"

GameObject::GameObject(const std::vector<int>& position)
        : position(position) {}

GameObject::GameObject(const int x, const int y, const int direction)
        : position(x, y, direction) {}

std::vector<int> GameObject::get_position() {
    return this->position.get_position();
}

GameObject::~GameObject() {}
