#pragma once
#include <memory>
#include "Graphics/RenderableObject.hpp"

class Tile {
	unsigned tileType;
	bool     collision;

	bool animated;
	bool animationRepeat;
	unsigned frame;
	unsigned animationSpeed;
	unsigned animationStartNumber;
	unsigned animationFrameCount;
public:
	Tile() = default;

	Tile(unsigned type, bool coll)
	: tileType(type), collision(coll), animated(false) {}

	Tile(unsigned int type, bool coll, unsigned aSpeed, unsigned aStart, unsigned aFrameCount, bool repeat)
	: tileType(type), collision(coll), animated(true), animationRepeat(repeat), frame(0), animationSpeed(aSpeed),
	  animationStartNumber(aStart), animationFrameCount(aFrameCount) {}

	void tickFrame() { ++frame; }

	bool isCollidable() const { return collision; }
	bool isAnimated() const  { return animated; }
	bool isAnimationRepeat() const { return animationRepeat; }

	unsigned getType() const { return tileType; }
	unsigned getFrame() const { return frame; }
	unsigned getAnimationSpeed() const { return animationSpeed; }
	unsigned getAnimationStart() const { return animationStartNumber; }
	unsigned getFrameCount() const { return animationFrameCount; }

	/*
	 *  Stały rozmiar kafelek mapy dla silnika
	 */
	static unsigned dimensions() {
		return 32;
	}

	static Vec2u offset(Vec2u pos, Direction dir) {
		switch(dir) {
			case Direction::Up:
				return Vec2u(pos.x, pos.y - 1);
			case Direction::Down:
				return Vec2u(pos.x, pos.y + 1);
			case Direction::Left:
				return Vec2u(pos.x-1, pos.y);
			case Direction::Right:
				return Vec2u(pos.x+1, pos.y);

			default:
				return Vec2u();
		}
	}
};