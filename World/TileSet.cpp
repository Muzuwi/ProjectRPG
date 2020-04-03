#include "TileSet.hpp"

TileSet::TileSet(const Spritesheet &mapSpritesheet)
: spritesheet(mapSpritesheet) {
	Vec2u size = {mapSpritesheet.getTexture().getSize().x / mapSpritesheet.getSpriteSize().x,
	              mapSpritesheet.getTexture().getSize().y / mapSpritesheet.getSpriteSize().y };
	for(unsigned type = 0; type < size.x * size.y; ++type) {
		tiles.push_back(Tile(0));
	}
}

