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
		return false;
	}

	auto interactionPos = Tile::offset(playerPos, player.getDirection());
	std::cout << "Player interacted with " <<  interactionPos.x << " " << interactionPos.y << "\n";

	auto* npc = currentMap.findNPC(interactionPos);
	if(npc) {
		Direction npcDir;
		if(player.getDirection() == Direction::Down) npcDir = Direction::Up;
		else if(player.getDirection() == Direction::Up) npcDir = Direction::Down;
		else if(player.getDirection() == Direction::Left) npcDir = Direction::Right;
		else if(player.getDirection() == Direction::Right) npcDir = Direction::Left;
		npc->onInteract(npcDir);
		return true;
	}

	return false;
}
