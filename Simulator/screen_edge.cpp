#include "screen_edge.h"
#include "constants.h"
#include "contact_listener.h"

class EdgeUserData {
public:
    EdgeUserData() {
    }
};

void createScreenEdges(b2World* world, unsigned int width, unsigned int height) {
    b2BodyDef edgeBodyDefinition;
    edgeBodyDefinition.position.Set(0.f, 0.f);
    b2Body* edgeBody = world->CreateBody(&edgeBodyDefinition);
    edgeBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(new BodyUserData{ Identifiers::ScreenEdge, nullptr });
    b2EdgeShape edgeShape;

    b2Vec2 lowerLeftCorner = b2Vec2(0, 0);
    b2Vec2 lowerRightCorner = b2Vec2(height / PhysicsConstants::pixelsPerMeter, 0);
    b2Vec2 upperLeftCorner = b2Vec2(0, width / PhysicsConstants::pixelsPerMeter);
    b2Vec2 upperRightCorner = b2Vec2(height / PhysicsConstants::pixelsPerMeter, width / PhysicsConstants::pixelsPerMeter);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &edgeShape;
    fixtureDef.density = 0;
    fixtureDef.filter.categoryBits = BitMasks::ScreenEdge;
    fixtureDef.filter.maskBits = BitMasks::MatchAll;
    edgeShape.SetTwoSided(lowerLeftCorner, lowerRightCorner);
    edgeBody->CreateFixture(&fixtureDef);
    edgeShape.SetTwoSided(lowerRightCorner, upperRightCorner);
    edgeBody->CreateFixture(&fixtureDef);
    edgeShape.SetTwoSided(upperRightCorner, upperLeftCorner);
    edgeBody->CreateFixture(&fixtureDef);
    edgeShape.SetTwoSided(upperLeftCorner, lowerLeftCorner);
    edgeBody->CreateFixture(&fixtureDef);
}