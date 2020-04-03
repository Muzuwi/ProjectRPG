#pragma once
#include "Entity/Player.hpp"
#include "Map.hpp"

class WorldManager {
	Map currentMap;
	Player player;

	static Direction flipDirection(Direction dir);
public:
	WorldManager()
	: currentMap(Map::make_empty({1,1},0)){ }

	Map& getMap() { return currentMap; };
	Player& getPlayer() { return player; };

	void loadMap(const std::string& mapName);

	bool moveActor(Actor &actor, Direction dir);
	bool movePlayer(Direction dir);

	bool playerInteract();

	void draw(sf::RenderTarget&);
};