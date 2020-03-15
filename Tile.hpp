#pragma once
#include "RenderableObject.hpp"

class Tile : public RenderableObject {
	unsigned tileType;
	unsigned mapPriority;
	bool     collision;
	//  Event event??

public:
	Tile() = default;
	Tile(unsigned type, unsigned priority, bool coll)
		: tileType(type), mapPriority(priority), collision(coll) {}

	unsigned getType() const { return tileType; }
	bool isCollidable() const { return collision; }

	virtual void draw(Vec2u position, sf::RenderTarget& target) override;
	virtual Vec2u getDimensions() const override;
};