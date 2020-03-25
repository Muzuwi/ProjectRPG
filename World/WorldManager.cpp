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
		switch(dir) {
			case Direction::Up: {
				if(!currentMap.checkCollision(actorPos.x, actorPos.y - 1)) {
					actor.move(Direction::Up);
					return true;
				}
				break;
			}

			case Direction::Down: {
				if(!currentMap.checkCollision(actorPos.x, actorPos.y + 1)) {
					actor.move(Direction::Down);
					return true;
				}
				break;
			}

			case Direction::Left: {
				if(!currentMap.checkCollision(actorPos.x - 1, actorPos.y)) {
					actor.move(Direction::Left);
					return true;
				}
				break;
			}

			case Direction::Right: {
				if(!currentMap.checkCollision(actorPos.x + 1, actorPos.y)) {
					actor.move(Direction::Right);
					return true;
				}
				break;
			}

			default: break;
		}
	}

	actor.setFacing(dir);
	return false;
}

bool WorldManager::movePlayer(Direction dir) {
	return moveActor(player, dir);
}
