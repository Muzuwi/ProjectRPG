#include "World/WorldManager.hpp"

void WorldManager::loadMap(const std::string &mapName) {
	currentMap = Map::from_file(mapName);
	currentMap.initializeVertexArrays();
}

bool WorldManager::movePlayer(Direction dir) {
	auto playerPos = player.getWorldPosition();
	bool invalidMovements = (playerPos.x == 0 && dir == Direction::Left) ||
							(playerPos.y == 0 && dir == Direction::Up)   ||
			(playerPos.x == currentMap.getWidth()-1 && dir == Direction::Right) ||
			(playerPos.y == currentMap.getHeight()-1 && dir == Direction::Down);

	if(!invalidMovements) {
		switch(dir) {
			case Direction::Up: {
				if(!currentMap.checkCollision(playerPos.x, playerPos.y-1)) {
					player.move(Direction::Up);
					return true;
				}
				break;
			}

			case Direction::Down: {
				if(!currentMap.checkCollision(playerPos.x, playerPos.y+1)) {
					player.move(Direction::Down);
					return true;
				}
				break;
			}

			case Direction::Left: {
				if(!currentMap.checkCollision(playerPos.x-1, playerPos.y)) {
					player.move(Direction::Left);
					return true;
				}
				break;
			}

			case Direction::Right: {
				if(!currentMap.checkCollision(playerPos.x+1, playerPos.y)) {
					player.move(Direction::Right);
					return true;
				}
				break;
			}

			default: break;
		}
	}

	player.setFacing(dir);
	return false;
}
