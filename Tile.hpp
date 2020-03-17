#pragma once
#include <memory>
#include "RenderableObject.hpp"

class Tile : public RenderableObject {
	unsigned tileType;
	unsigned mapPriority;
	bool     collision;
	//  Event event??
	unsigned frame;

public:
	Tile() = default;
	Tile(unsigned type, unsigned priority, bool coll)
		: tileType(type), mapPriority(priority), collision(coll), frame(0) {}

	unsigned getType() const { return tileType; }
	bool isCollidable() const { return collision; }

	virtual void draw(sf::RenderTarget& target) override {};
	virtual void draw(Vec2u position, sf::RenderTarget& target) override;
	virtual Vec2u getDimensions() const override;
	virtual void frameTick() override {frame = (frame + 1) % (48*30);};
};