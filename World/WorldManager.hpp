#pragma once
#include <unordered_map>
#include "Entity/Player.hpp"
#include "Map.hpp"

class WorldManager {
	std::shared_ptr<Map> currentMap;
	Player player;

	static const int mapTravelTime = 10;
	struct {
		bool isTravelling;
		int currentMapTravelTime = 0;
	} MapTravel;

	std::unordered_map<std::string, std::shared_ptr<Map>> allMaps;
public:
	WorldManager() {
		allMaps["_undefined"] = std::make_shared<Map>(Map::make_empty({1,1},0));
		allMaps["_undefined"]->initializeVertexArrays();
		allMaps["_undefined"]->bindPlayer(player);
		currentMap = allMaps["_undefined"];
	}

	Map& getMap() {
		if(!currentMap)
			throw std::runtime_error("WorldManager: getMap() called but no map loaded");
		return *currentMap;
	}

	Player& getPlayer() { return player; };

	void loadMap(const std::string& mapName);

	bool movePlayer(Direction dir);
	bool playerInteract();

	bool handleMapTransfer(Connection conn);

	void draw(sf::RenderTarget&);
	void updateWorld();
};