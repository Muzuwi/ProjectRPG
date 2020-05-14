#pragma once
#include <vector>
#include <string>
#include <memory>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity/Player.hpp"
#include "Tile.hpp"
#include "Types.hpp"
#include "Entity/NPC.hpp"
#include "World/TileSet.hpp"
#include "AssetManager.hpp"

struct Connection {
	Vec2u sourcePos;
	std::string targetMap;
	Vec2u targetPos;
};

class Map {
	struct {
		Connection goingThroughConnection;
		bool valid = false;
	} standingOnConnection;

	std::string tilesetName;

	Vec2u size;

	TileSet tileset;
	Array2D<unsigned> floorTiles[3];
	std::vector<std::shared_ptr<NPC>>   npcs;

	const Player* player;

	std::array<sf::VertexArray, 5> vertices;
	//  FIXME: Nieoptymalne! Ale wymagane w edytorze
	std::array<sf::VertexArray, 3> layerVertices;

	sf::VertexBuffer buffer[5];

	std::vector<Connection> connections;
protected:
	void drawSpecial(sf::RenderTarget&);
	void drawTiles(sf::RenderTarget&);
	void drawTiles(sf::RenderTarget&, unsigned);
	void drawEntities(sf::RenderTarget&);
	Map(Vec2u size, const std::string& tileset);

	void serializeToFile(const std::string& file);
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

	void draw(sf::RenderTarget&);
	void initializeVertexArrays();

	void updateActors();

	bool moveActor(Actor &actor, Direction dir);

	NPC* findNPC(Vec2u pos);

	void bindPlayer(const Player& _player) {
		player = &_player;
	}

	void onStepHook(Vec2u pos);

	const std::vector<Connection>& getConnections() const {
		return connections;
	}

	bool standingConnectionValid() const {
		return standingOnConnection.valid;
	}

	Connection getStandingConnection() {
		standingOnConnection.valid = false;
		return standingOnConnection.goingThroughConnection;
	}

	friend class EditWindow;
	friend class NPCCreator;
	friend class Brush;
	friend class ConnectionTool;
};