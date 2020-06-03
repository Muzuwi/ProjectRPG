#include <algorithm>
#include "World/WorldManager.hpp"
#include "Sound/SoundEngine.hpp"

static bool s_should_save_game {false};
static bool s_should_load_game {false};

void WorldManager::setCurrentMap(const std::string &mapName) {
	try {
		currentMap = AssetManager::getMap(mapName);
		currentMap->bindPlayer(player);
		currentMapName = mapName;
		std::cout << "play music: '" << currentMap->music() << "'\n";
		if(!currentMap->music().empty())
			SoundEngine::get().playMusic(currentMap->music(), true);
	} catch (std::exception&) {
		std::cerr << "Failed loading map " << mapName << "\n";
		return;
	}
}

bool WorldManager::movePlayer(Direction dir) {
	bool ret = currentMap->moveActor(player, dir);
	return ret;
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
	if(MapTravel.isTravelling) {
		//  Fade out
		if(MapTravel.currentMapTravelTime < 0) {
			sf::RectangleShape rect;
			rect.setPosition(0,0);
			rect.setSize(Vec2f(currentMap->getWidth() * Tile::dimensions(), currentMap->getHeight() * Tile::dimensions()));
			auto alpha = 255 - (unsigned)(((double)-1*MapTravel.currentMapTravelTime/mapTravelTime) * 255);
			rect.setFillColor(sf::Color(0, 0, 0, alpha));

			currentMap->draw(target);
			target.draw(rect);
			MapTravel.currentMapTravelTime++;
		}
		//  Actually change the map once fully opaque
		else if(MapTravel.currentMapTravelTime == 0) {
			assert(currentMap->standingConnectionValid());
			this->handleMapTransfer(currentMap->getStandingConnection());
			MapTravel.currentMapTravelTime++;
		}
		//  Fade in
		else {
			sf::RectangleShape rect;
			rect.setPosition(0,0);
			rect.setSize(Vec2f(currentMap->getWidth() * Tile::dimensions(), currentMap->getHeight() * Tile::dimensions()));
			auto alpha = (unsigned)(((double)-1*MapTravel.currentMapTravelTime/mapTravelTime) * 255);
			rect.setFillColor(sf::Color(0, 0, 0, alpha));

			currentMap->draw(target);
			target.draw(rect);
			MapTravel.currentMapTravelTime++;
			if(MapTravel.currentMapTravelTime > mapTravelTime)
				MapTravel.isTravelling = false;
		}
	} else {
		currentMap->draw(target);
	}
}

/*
 *  Aktualizuje wszystkich aktorów świata oraz inne animacje
 */
void WorldManager::updateWorld() {
	if(s_should_save_game) {
		saveGame();
		s_should_save_game = false;
	}

	if(s_should_load_game) {
		loadGame();
		s_should_load_game = false;
	}

	player.update();
	currentMap->updateActors();
	if(!player.isMoving && currentMap->standingConnectionValid() && !MapTravel.isTravelling) {
		MapTravel.isTravelling = true;
		MapTravel.currentMapTravelTime = -1 * mapTravelTime;
	}
}

bool WorldManager::handleMapTransfer(Connection conn) {
	try {
		setCurrentMap(conn.targetMap);
	} catch (std::exception&) {
		std::cerr << "Failed loading map " << conn.targetMap << "\n";
		return false;
	}

	Vec2u worldPos {conn.targetPos};
	worldPos.x = std::clamp(worldPos.x, 0u, this->currentMap->getWidth());
	worldPos.y = std::clamp(worldPos.y, 0u, this->currentMap->getHeight());
	player.setPosition(worldPos);
} 

void WorldManager::shouldSaveGame() {
	s_should_save_game = true;
}

void WorldManager::shouldLoadGame() {
	s_should_load_game = true;
}

void WorldManager::saveGame() {
	auto save = AssetManager::getSavefile();
	save.set("playerCurrentMap", currentMapName);
	save.set("playerCurrentPos", player.getWorldPosition());
	player.saveToSavegame();
	save.saveToFile();
	std::cout << "Game saved successfully\n";
}

void WorldManager::loadGame() {
	auto save = AssetManager::getSavefile();
	try {
		setCurrentMap(save.get<std::string>("playerCurrentMap"));

		auto worldPos = save.get<Vec2u>("playerCurrentPos");
		worldPos.x = std::clamp(worldPos.x, 0u, this->currentMap->getWidth());
		worldPos.y = std::clamp(worldPos.y, 0u, this->currentMap->getHeight());
		player.setPosition(worldPos);

		player.getInventory().loadFromSavegame();
	} catch (std::exception&) {
		std::cerr << "Failed loading game!\n";
		return;
	}
}
