#pragma once
#include <memory>
#include "Graphics/RenderableObject.hpp"
#include "Types.hpp"

enum CollisionMask {
	Collision_Down  = (1u << (unsigned)Direction::Down),
	Collision_Left  = (1u << (unsigned)Direction::Left),
	Collision_Right = (1u << (unsigned)Direction::Right),
	Collision_Up    = (1u << (unsigned)Direction::Up)
};

class Tile {
	bool     collision[4];
	unsigned priority;
public:
	Tile() {
		priority = 0;
		for(unsigned i = 0; i < 4; i++)
			collision[i] = false;
	}
	Tile(unsigned collisionBitmap) {
		for(unsigned i = 0; i < 4; i++)
			collision[i] = collisionBitmap & (1 << i);
		priority = 0;
	}

	Tile(unsigned collisionBitmap, unsigned _priority)
	: Tile(collisionBitmap) {
		priority = _priority;
	}

	bool collisionCheck(Direction dir) const {
		return collision[(unsigned)dir];
	}

	unsigned getPriority() const {
		return priority;
	}

	unsigned getCollisionBitmap() const {
		unsigned n = 0;

		for(unsigned i = 0; i < 4; i++)
			n |= (collision[i] << i);

		return n;
	}

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

	friend class TilesetEditor;
};