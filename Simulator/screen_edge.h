#pragma once
#include "box2d/box2d.h"
#include <memory>


extern void createScreenEdges(std::shared_ptr<b2World> world, unsigned int width, unsigned int height);