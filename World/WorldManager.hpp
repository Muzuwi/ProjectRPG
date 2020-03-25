#pragma once
#include "Entity/Player.hpp"
#include "Map.hpp"

class WorldManager {
	Map currentMap;
	Player player;

public:
	WorldManager() { }

	Map& getMap() { return currentMap; };
	Player& getPlayer() { return player; };

	void loadMap(const std::string& mapName);
};