#pragma once
#include "Types.hpp"

class WorldEntity {
protected:
	unsigned entityType;
	Vec2f worldPosition;
public:
	WorldEntity(unsigned type, Vec2f position) : entityType(type), worldPosition(position) {}

	Vec2f getWorldPosition() const { return worldPosition; }

	virtual void onInteract() = 0;
	virtual void onStep() = 0;
	virtual bool collisionCheck(WorldEntity&) = 0;
	virtual void update() = 0;
};