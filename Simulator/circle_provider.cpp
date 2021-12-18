#include "circle_provider.h"

CircleProvider::CircleProvider(int radiusPixelsIn, sf::Color colorIn) : radiusPixels(radiusPixelsIn), color(colorIn)
{

}

ShapeDefinition CircleProvider::get() const
{
    ShapeDefinition result = {
        std::make_shared<sf::CircleShape>(this->radiusPixels),
        std::make_shared<b2CircleShape>()
    };
    result.shape->setFillColor(color);
    result.shape->setOrigin(radiusPixels, radiusPixels);
    result.b2Shape->m_radius = radiusPixels / PhysicsConstants::pixelsPerMeter;
    return result;
}
