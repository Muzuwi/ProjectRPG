#include <memory>
#include "Engine.h"

Engine::Engine() {

}

Engine::~Engine() {

}

bool Engine::Init() {
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(windowWidth, windowHeight, 32), "Projekt");
	newMap = Map::from_file("");
	LoadTextures();
	if (!window) return false;
	return true;
}

void Engine::LoadTextures() {
	textureManager.addSpritesheet("sprite1.png");
	textureManager.addSpritesheet("sprite2.png");
	textureManager.addSpritesheet("playersprite.png");
	textureManager.addSpritesheet("spritesheets.png");
}

void Engine::RenderFrame() {
	window->clear();
	RenderTile();
	RenderTilePass2();
	RenderEntity();
	window->display();
}

void Engine::ProcessInput() {
	sf::Event event;
	while (window->pollEvent(event)) {
		switch(event.type) {
			case sf::Event::Closed: {
				window->close();
				break;
			}
			case sf::Event::KeyPressed: {
				tempPlayer.handleKeyboardEvent(true, event.key);
				break;
			}
			case sf::Event::KeyReleased: {
				tempPlayer.handleKeyboardEvent(false, event.key);
				break;
			}
			default: break;
		}
	}
}

void Engine::Update() {
	//camera->Update();
}

void Engine::MainLoop() {
	while (window->isOpen()) {
		ProcessInput();
		Update();
		RenderFrame();
	}
}

void Engine::Start() {
	if (!Init()) throw "Blad w inicjalizacji silnika";
	MainLoop();
}

void Engine::RenderTile() {
	unsigned tilesX = (windowWidth / 32),
			tilesY = (windowHeight / 32);

	auto playerPos = tempPlayer.getWorldPosition();
	auto playerTilePos = playerPos / 32.0f;

	auto drawTilesStartingFrom = [&](Vec2u startpoint) {
		for(unsigned i = startpoint.x; i < tilesX + + startpoint.x; i++) {
			for(unsigned j = startpoint.y; j < tilesY + + startpoint.y; j++) {
				if(i >= 100 || j >= 100) continue;

				auto& tile = newMap.getTile({i, j});
				auto position = Vec2u {(i - startpoint.x) * tile.getDimensions().x,
				                       (j - startpoint.y) * tile.getDimensions().y};
				tile.draw(position, *this->window);
				tile.frameTick();
			}
		}
	};

	auto centerTile = Vec2u {tilesX / 2, tilesY / 2};
	auto centerDiffFromPlayer = Vec2i {(int)playerTilePos.x - (int)centerTile.x, (int)playerTilePos.y - (int)centerTile.y};
	Vec2u start {0, 0};
	if(centerDiffFromPlayer.x > 0)
		start.x = centerDiffFromPlayer.x;
	if(centerDiffFromPlayer.y > 0)
		start.y = centerDiffFromPlayer.y;

	drawTilesStartingFrom(start);
}

void Engine::RenderTilePass2() {

}

void Engine::RenderEntity() {
	tempPlayer.draw(*this->window);
}
