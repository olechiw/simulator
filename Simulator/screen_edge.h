#pragma once
#include <memory>

#include "box2d/box2d.h"
#include "constants.h"
#include "contact_listener.h"
#include "object_identifier.h"



extern void createScreenEdges(std::shared_ptr<b2World> world, unsigned int width, unsigned int height);