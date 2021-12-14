#include "renderable.h"

bool Renderable::isDestroyed()
{
    return this->destroyed;
}

void Renderable::destroy()
{
    this->destroyed = true;
}

Renderable::~Renderable() {}