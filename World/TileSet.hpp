#pragma once
#include <memory>
#include "Graphics/Spritesheet.hpp"
#include "World/Tile.hpp"

class TileSet {
	std::vector<Tile> tiles;
	std::reference_wrapper<const Spritesheet> spritesheet;
	std::string setName;

	void serializeToFile();
public:
	TileSet(const Spritesheet& mapSpritesheet, const std::string& name);

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

	friend class TilesetEditor;
};