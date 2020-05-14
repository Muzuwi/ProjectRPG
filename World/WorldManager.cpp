#include "World/WorldManager.hpp"

void WorldManager::loadMap(const std::string &mapName) {
	try {
		allMaps[mapName] = std::make_shared<Map>(Map::from_file(mapName));
	} catch (std::exception&) {
		std::cerr << "Failed loading map " << mapName << "\n";
		return;
	}
	allMaps[mapName]->initializeVertexArrays();
	allMaps[mapName]->bindPlayer(player);
	currentMap = allMaps[mapName];
}

bool WorldManager::movePlayer(Direction dir) {
	return currentMap->moveActor(player, dir);
}

bool WorldManager::playerInteract() {
	auto playerPos = player.getWorldPosition();
	bool invalidInteract = (playerPos.x == 0 && player.getDirection() == Direction::Left) ||
	                        (playerPos.y == 0 && player.getDirection() == Direction::Up) ||
	                        (playerPos.x == currentMap->getWidth() - 1 && player.getDirection() == Direction::Right) ||
	                        (playerPos.y == currentMap->getHeight() - 1 && player.getDirection() == Direction::Down);
	if(invalidInteract) {
		return false;
	}

	auto interactionPos = Tile::offset(playerPos, player.getDirection());

	auto* npc = currentMap->findNPC(interactionPos);
	if(npc) {
		npc->onInteract(Actor::flipDirection(player.getDirection()));
		return true;
	}

	return false;
}

/*
 *  Ogólna funkcja do wyrenderowania całej mapy do danego targetu
 */
void WorldManager::draw(sf::RenderTarget &target) {
	currentMap->draw(target);
}

/*
 *  Aktualizuje wszystkich aktorów świata oraz inne animacje
 */
void WorldManager::updateWorld() {
	player.update();
	currentMap->updateActors();
}
