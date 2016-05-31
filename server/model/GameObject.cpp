#include <vector>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Box2D.h>

#include "GameObject.h"

GameObject::GameObject(const std::vector<int>& position)
        : position(position) {}

GameObject::GameObject(const int x, const int y, const int direction)
        : position(x, y, direction) {}

void GameObject::create_fixture(b2Shape* shape) {
    // note that friction, etc. can be modified later by looping
    // over the body's fixtures and calling fixture->SetFriction()
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.7f;
    fixtureDef.restitution = 0.1f;
    fixtureDef.filter.categoryBits = 0x02;
    fixtureDef.filter.maskBits = 0xffff;
    this->body->CreateFixture(&fixtureDef);
}

void GameObject::add_rectangular_fixture_to_body() {
    b2PolygonShape shape;
    //width * scale, height * scale
    shape.SetAsBox(100, 100);
    this->create_fixture(&shape);
}

void GameObject::set_body(b2Body* body) {
    this->body = body;
    //Por ahora son todos iguales
    this->add_rectangular_fixture_to_body();
}


std::vector<int> GameObject::get_position() {
    return this->position.get_position();
}

GameObject::~GameObject() {}
