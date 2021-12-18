#include "polygon_provider.h"

PolygonProvider::PolygonProvider(float radiusPixelsIn, sf::Color colorIn, int numberOfSidesIn) : radiusPixels(radiusPixelsIn), color(colorIn), numberOfSides(numberOfSidesIn)
{

}


ShapeDefinition PolygonProvider::get() const
{
    auto polygon = std::make_shared<b2PolygonShape>();
    ShapeDefinition result = {
        std::make_shared<sf::CircleShape>(this->radiusPixels, this->numberOfSides),
        polygon
    };
    result.shape->setFillColor(color);
    result.shape->setOrigin(this->radiusPixels, this->radiusPixels);

    b2Vec2* vertices = new b2Vec2[this->numberOfSides];
    for (int i = 0; i < this->numberOfSides; ++i)
    {
        float angle = (2.f * i * static_cast<float>(Math::pi) / this->numberOfSides) + Math::pi / 2.f;
        vertices[i] = {
            radiusPixels * std::cos(angle) / PhysicsConstants::pixelsPerMeter,
            radiusPixels * std::sin(angle) / PhysicsConstants::pixelsPerMeter
        };
    }
    polygon->Set(vertices, this->numberOfSides);
    delete[] vertices;
    return result;
}
