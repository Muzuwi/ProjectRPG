#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <Entity/Player.hpp>
#include "Tile.hpp"
#include "Types.hpp"
#include "Entity/NPC.hpp"

class Map {
	Vec2u size;

	Array2D<Tile> floorTiles;

	struct Decor {
		Vec2u pos;
		Tile decor;
		Decor(Vec2u _pos, Tile _tile)
		: pos(_pos), decor(_tile) { }
	};
	std::vector<Decor> tileDecors;
	std::vector<NPC>   npcs;

	sf::VertexArray vertices;
	std::vector<Vec2u> animatedTiles;

	void drawTiles(sf::RenderTarget&);
	void drawDecor(sf::RenderTarget&);
	void drawEntities(sf::RenderTarget&, const Player& player);
public:
	~Map() = default;

	static Map from_file(const std::string& path);
	static Map make_empty(Vec2u size);

	Tile& getTile(unsigned x, unsigned y) { return floorTiles[x][y]; }
	Tile& getTile(Vec2u pos) { return floorTiles[pos.x][pos.y]; }

	unsigned getWidth() const { return size.x; }
	unsigned getHeight() const { return size.y; }

	//  FIXME:  Const
	bool checkCollision(Vec2u pos);
	bool checkCollision(unsigned x, unsigned y);

	Map(const Map&);

	Map() { }

	void draw(sf::RenderTarget&, const Player&);
	void initializeVertexArrays();

	NPC* findNPC(Vec2u pos);
	NPC* findNPC(unsigned x, unsigned y);
};