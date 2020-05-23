#pragma once
#include <unordered_map>
#include "Entity/Player.hpp"
#include "Map.hpp"

class WorldManager {
	std::shared_ptr<Map> currentMap;
	Player player;

	static const int mapTravelTime {10};
	struct {
		bool isTravelling {false};
		int currentMapTravelTime {0};
	} MapTravel;
public:
	WorldManager() {}

	Map& getMap() {
		if(!currentMap)
			throw std::runtime_error("WorldManager: getMap() called but no map loaded");
		return *currentMap;
	}

	Player& getPlayer() { return player; };

	void setCurrentMap(const std::string& mapName);

	bool movePlayer(Direction dir);
	bool playerInteract();

	bool handleMapTransfer(Connection conn);

	void draw(sf::RenderTarget&);
	void updateWorld();
};