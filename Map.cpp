#include <fstream>
#include "TextureManager.hpp"
#include "Map.hpp"

/*
 *  Ładuje mapę z pliku i zwraca go w obiekcie klasy Map
 *
 *  Narazie mapa jest hardcodowana, ale ewentualnie będziemy tu ładować mapę z pliku.
 */
Map Map::from_file(const std::string&) {
	Map newMap;
	newMap.size = {100 , 100};
	newMap.floorTiles.resize(100, 100);
	for(size_t i = 0; i < 100; i++) {
		for(size_t j = 0; j < 100; j++) {
			unsigned type = 0;
			if(i == 0 || j == 0 || i == 99 || j == 99) type = 1;
			if(i % 8 == 0) type = 1;
			if(i == 10 && j == 10) type = 2;

			if(i == 20 && j == 20)
				newMap.floorTiles[i][j] = Tile(0, false, 4, 0, 3, true);
			else
				newMap.floorTiles[i][j] = Tile(type, false);

			if(!(rand() % 25))
				newMap.tileDecors.push_back(Decor(Vec2u(i,j),Tile(4+(i%4), false)));
		}
	}

	newMap.tileDecors.push_back(
			Decor( Vec2u(5, 5),
			       {
					Tile(3, true, 4, 3, 4, true)
			       }
				)
			);

	return newMap;
}

Map::Map(const Map &map) {
	this->size = map.size;
	this->floorTiles = map.floorTiles;
	this->tileDecors = map.tileDecors;
	this->vertices = map.vertices;
	this->animatedTiles = map.animatedTiles;
}

void Map::draw(sf::RenderTarget &target) {
	static auto& tileset = TextureManager::get()->getSpritesheet("Tileset");

	for(const auto& coords : animatedTiles) {
		sf::Vertex* quad = &vertices[(coords.x+coords.y*100)*4];
		auto& tile = floorTiles[coords.x][coords.y];

		auto currentAnimationFrame = tile.getAnimationStart() + (tile.getFrame() / tile.getAnimationSpeed());
		if(currentAnimationFrame > tile.getFrameCount() && tile.isAnimationRepeat())
			currentAnimationFrame %= tile.getFrameCount();
		else
			currentAnimationFrame = tile.getAnimationStart();

		auto textureCoords = TextureManager::get()->getSpritesheet("Tileset").getTextureCoordinates(0, currentAnimationFrame);
		quad[0].texCoords = sf::Vector2f(textureCoords.left, textureCoords.top);
		quad[1].texCoords = sf::Vector2f(textureCoords.left+textureCoords.width, textureCoords.top);
		quad[2].texCoords = sf::Vector2f(textureCoords.left+textureCoords.width, textureCoords.top+textureCoords.height);
		quad[3].texCoords = sf::Vector2f(textureCoords.left, textureCoords.top+textureCoords.height);

		tile.tickFrame();
	}

	target.draw(vertices, &tileset.getTexture());

	for(auto& decoration : tileDecors) {
		auto& tile = decoration.decor;

		unsigned currentAnimationFrame = tile.getType();
		if(tile.isAnimated()) {
			currentAnimationFrame = tile.getAnimationStart() + (tile.getFrame() / tile.getAnimationSpeed());
			if(currentAnimationFrame > tile.getFrameCount() && tile.isAnimationRepeat())
				currentAnimationFrame = tile.getAnimationStart() + (currentAnimationFrame % tile.getFrameCount());
			else
				currentAnimationFrame = tile.getAnimationStart();
			tile.tickFrame();
		}

		auto sprite = tileset.getSprite(0, currentAnimationFrame);
		sprite.setPosition(Vec2f(decoration.pos * Tile::dimensions()));
		target.draw(sprite);
	}
}

void Map::initializeVertexArrays() {
	vertices = sf::VertexArray(sf::Quads, 100*100*4);

	for(unsigned i = 0; i < size.x; i++) {
		for(unsigned j = 0; j < size.y; j++) {
			sf::Vertex* quad = &vertices[(i+j*100)*4];
			quad[0].position = sf::Vector2f(i * Tile::dimensions(), j * Tile::dimensions());
			quad[1].position = sf::Vector2f((i + 1) * Tile::dimensions(), j * Tile::dimensions());
			quad[2].position = sf::Vector2f((i + 1) * Tile::dimensions(), (j + 1) * Tile::dimensions());
			quad[3].position = sf::Vector2f(i * Tile::dimensions(), (j + 1) * Tile::dimensions());

			auto& tile = floorTiles[i][j];
			auto textureCoords = TextureManager::get()->getSpritesheet("Tileset").getTextureCoordinates(0, tile.getType());
			quad[0].texCoords = sf::Vector2f(textureCoords.left, textureCoords.top);
			quad[1].texCoords = sf::Vector2f(textureCoords.left+textureCoords.width, textureCoords.top);
			quad[2].texCoords = sf::Vector2f(textureCoords.left+textureCoords.width, textureCoords.top+textureCoords.height);
			quad[3].texCoords = sf::Vector2f(textureCoords.left, textureCoords.top+textureCoords.height);

			//  Zapisz wszystkie animowane kafle do osobnego wektora
			if(tile.isAnimated()) {
				animatedTiles.push_back({i, j});
			}
		}
	}
}

bool Map::checkCollision(unsigned x, unsigned y) {
	assert(x < size.x && y < size.y);

	bool tileCollision = floorTiles[x][y].isCollidable();
	if(tileCollision) return true;

	for(auto& decor : tileDecors) {
		if(decor.pos.x == x && decor.pos.y == y) {
			return decor.decor.isCollidable();
		}
	}

	return false;
}

bool Map::checkCollision(Vec2u pos) {
	return this->checkCollision(pos.x, pos.y);
}
