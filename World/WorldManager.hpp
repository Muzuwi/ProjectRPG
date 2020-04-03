#pragma once
#include "Entity/Player.hpp"
#include "Map.hpp"

class WorldManager {
	Map currentMap;
	Player player;

public:
	WorldManager()
	: currentMap(Map::make_empty({1,1},0)){ }

	Map& getMap() { return currentMap; };
	Player& getPlayer() { return player; };

	void loadMap(const std::string& mapName);

	bool movePlayer(Direction dir);
	bool playerInteract();

	void draw(sf::RenderTarget&);
	void updateWorld();
};