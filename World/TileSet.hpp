#pragma once
#include <memory>
#include "Graphics/Spritesheet.hpp"
#include "World/Tile.hpp"

class TileSet {
	std::vector<Tile> tiles;
	std::reference_wrapper<const Spritesheet> spritesheet;
public:
	TileSet(const Spritesheet& mapSpritesheet);

	Tile getTile(unsigned type) const {
		assert(type < tiles.size());
		return tiles[type];
	}

	const Spritesheet& getSpritesheet() const {
		return spritesheet.get();
	}

	const sf::Texture& getTexture() const {
		return spritesheet.get().getTexture();
	}
};