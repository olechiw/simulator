#pragma once
#include "shape_definition.h"

class ShapeDefinitionProvider {
public:
	virtual ~ShapeDefinitionProvider() = default;
	virtual ShapeDefinition get() const = 0;
};