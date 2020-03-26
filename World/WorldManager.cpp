#include "World/WorldManager.hpp"

void WorldManager::loadMap(const std::string &mapName) {
	currentMap = Map::from_file(mapName);
	currentMap.initializeVertexArrays();
}

bool WorldManager::moveActor(Actor &actor, Direction dir) {
	auto actorPos = actor.getWorldPosition();
	bool invalidMovements = (actorPos.x == 0 && dir == Direction::Left) ||
	                        (actorPos.y == 0 && dir == Direction::Up) ||
	                        (actorPos.x == currentMap.getWidth() - 1 && dir == Direction::Right) ||
	                        (actorPos.y == currentMap.getHeight() - 1 && dir == Direction::Down);

	if(!invalidMovements) {
		if(!currentMap.checkCollision(Tile::offset(actorPos, dir))) {
			actor.move(dir);
			return true;
		}
	}

	actor.setFacing(dir);
	return false;
}

bool WorldManager::movePlayer(Direction dir) {
	return moveActor(player, dir);
}

bool WorldManager::playerInteract() {
	auto playerPos = player.getWorldPosition();
	bool invalidInteract = (playerPos.x == 0 && player.getDirection() == Direction::Left) ||
	                        (playerPos.y == 0 && player.getDirection() == Direction::Up) ||
	                        (playerPos.x == currentMap.getWidth() - 1 && player.getDirection() == Direction::Right) ||
	                        (playerPos.y == currentMap.getHeight() - 1 && player.getDirection() == Direction::Down);
	if(invalidInteract) {
		std::cout << "Player would interact with outside of map\n";
		return false;
	}

	auto interactionPos = Tile::offset(playerPos, player.getDirection());
	std::cout << "Player interacted with " <<  interactionPos.x << " " << interactionPos.y << "\n";


	return false;
}
