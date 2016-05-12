#include "Object.h"

Object::Object(const char position) : position(position) {}

Object::~Object() {}

Stairs::Stairs(const char position) : Object(position) {}

Stairs::~Stairs() {}

Spike::Spike(const char position) : Object(position) {}

Spike::~Spike() {}

Block::Block(const char position) : Object(position) {}

Block::~Block() {}
