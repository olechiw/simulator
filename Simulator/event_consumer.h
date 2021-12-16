#pragma once
class EventConsumer
{
public:
	virtual ~EventConsumer() = default;
	virtual void onPhysicsUpdated() = 0;
};