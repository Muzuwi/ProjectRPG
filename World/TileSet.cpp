#include "TileSet.hpp"

/*
 *  Tutaj będziemy ładowali z pliku dane na temat kafli i ich kolizji
 */
TileSet::TileSet(const Spritesheet &mapSpritesheet)
: spritesheet(mapSpritesheet) {
	Vec2u size = {mapSpritesheet.getTexture().getSize().x / mapSpritesheet.getSpriteSize().x,
	              mapSpritesheet.getTexture().getSize().y / mapSpritesheet.getSpriteSize().y };
	for(unsigned type = 0; type < size.x * size.y; ++type) {
		//  FIXME:
		if(type == 3)
			tiles.push_back(Tile(Collision_Up | Collision_Down));
		else
			tiles.push_back(Tile(0));
	}
}

