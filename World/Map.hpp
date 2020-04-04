#pragma once
#include <vector>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <Entity/Player.hpp>
#include "Tile.hpp"
#include "Types.hpp"
#include "Entity/NPC.hpp"
#include "World/TileSet.hpp"
#include "Graphics/TextureManager.hpp"

class Map {
	Vec2u size;

	TileSet tileset;
	Array2D<unsigned> floorTiles[3];
	std::vector<Vec2u> animatedTiles[3];
	std::vector<std::shared_ptr<NPC>>   npcs;

	sf::VertexArray vertices;
protected:
	void drawTiles(sf::RenderTarget&);
	void drawTiles(sf::RenderTarget&, unsigned);
	void drawEntities(sf::RenderTarget&, const Player& player);
	void updateVertexAt(Vec2u pos, unsigned layer);
	Map(Vec2u size, const std::string& tileset);
public:
	Map(const Map&);
	~Map() = default;

	static Map from_file(const std::string& path);
	static Map make_empty(Vec2u size, unsigned defType, const std::string& tilesetName="Tileset");

	unsigned& getType(Vec2u pos, unsigned layer) {
		assert(layer < 3);
		return floorTiles[layer][pos.x][pos.y];
	}

	unsigned getWidth() const { return size.x; }
	unsigned getHeight() const { return size.y; }

	//  FIXME:  Const
	bool checkCollision(Vec2u pos, Direction dir, Actor& ref);

	void draw(sf::RenderTarget&, const Player&);
	void initializeVertexArrays();

	void updateActors();

	bool moveActor(Actor &actor, Direction dir);

	NPC* findNPC(Vec2u pos);

	friend class EditWindow;
	friend class NPCCreator;
	friend class Brush;
};