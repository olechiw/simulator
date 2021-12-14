#include "screen_edge.h"
#include "constants.h"
#include "contact_listener.h"

class EdgeUserData : public CollisionHandler {
public:
    EdgeUserData(): CollisionHandler(false, Constants::Identifiers::Edge) {
    }
};

void createScreenEdges(b2World* world, unsigned int width, unsigned int height) {
    b2BodyDef edgeBodyDefinition;
    edgeBodyDefinition.position.Set(0.f, 0.f);
    b2Body* edgeBody = world->CreateBody(&edgeBodyDefinition);
    edgeBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(new EdgeUserData());
    b2EdgeShape edgeShape;

    b2Vec2 lowerLeftCorner = b2Vec2(0, 0);
    b2Vec2 lowerRightCorner = b2Vec2(height / Constants::pixelsPerMeter, 0);
    b2Vec2 upperLeftCorner = b2Vec2(0, width / Constants::pixelsPerMeter);
    b2Vec2 upperRightCorner = b2Vec2(height / Constants::pixelsPerMeter, width / Constants::pixelsPerMeter);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &edgeShape;
    fixtureDef.density = 0;
    fixtureDef.filter.categoryBits = Constants::projectilesCategory;
    fixtureDef.filter.maskBits = Constants::projectilesCategory;
    edgeShape.SetTwoSided(lowerLeftCorner, lowerRightCorner);
    edgeBody->CreateFixture(&fixtureDef);
    edgeShape.SetTwoSided(lowerRightCorner, upperRightCorner);
    edgeBody->CreateFixture(&fixtureDef);
    edgeShape.SetTwoSided(upperRightCorner, upperLeftCorner);
    edgeBody->CreateFixture(&fixtureDef);
    edgeShape.SetTwoSided(upperLeftCorner, lowerLeftCorner);
    edgeBody->CreateFixture(&fixtureDef);
}