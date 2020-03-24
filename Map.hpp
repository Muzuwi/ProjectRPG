#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "Types.hpp"

class Map {
	Vec2u size;

	Array2D<Tile> tiles;
	//  Array2D<Event> events;
	//  Array2D<Entity> entities;

	sf::VertexArray vertices;
	std::vector<Vec2u> animatedTiles;
public:
	~Map() = default;

	static Map from_file(const std::string& path);

	Tile& getTile(unsigned x, unsigned y) { return tiles[x][y]; }
	Tile& getTile(Vec2u pos) { return tiles[pos.x][pos.y]; }

	unsigned getWidth() const { return size.x; }
	unsigned getHeight() const { return size.y; }

	Map(const Map&);

	Map() { }

	void draw(sf::RenderTarget&);
	void initializeVertexArrays();
};