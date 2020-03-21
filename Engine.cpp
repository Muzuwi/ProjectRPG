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
	sf::RenderTexture texture {};
	auto textureSize = Vec2u(newMap.getWidth() * 32u, newMap.getHeight() * 32u);
	if(!texture.create(textureSize.x, textureSize.y))
		throw std::runtime_error("Failed creating texture for display");

	RenderTile(texture);
	RenderTilePass2(texture);
	RenderEntity(texture);

	texture.display();

	auto playerCentre = tempPlayer.getWorldPosition() + Vec2f(tempPlayer.getDimensions()/2u);
	Vec2f viewCenter = playerCentre;

	if(playerCentre.x + (windowWidth/2.0f) > textureSize.x)
		viewCenter.x = textureSize.x - (windowWidth/2.0f);
	if(playerCentre.y + (windowHeight/2.0f) > textureSize.y)
		viewCenter.y = textureSize.y - (windowHeight/2.0f);
	if(playerCentre.x - (windowWidth/2.0f) < 0)
		viewCenter.x = (windowWidth/2.0f);
	if(playerCentre.y - (windowHeight/2.0f) < 0)
		viewCenter.y = (windowHeight/2.0f);

	sf::View view(viewCenter, Vec2f(windowWidth, windowHeight));
	window->setView(view);
	window->draw(sf::Sprite(texture.getTexture()));
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

/*
 *  Rysowanie wszystkich kafelek/ziemi, czyli głównie elementy statyczne
 */
void Engine::RenderTile(sf::RenderTarget& target) {
	for(unsigned i = 0; i < newMap.getWidth(); i++) {
		for(unsigned j = 0; j < newMap.getHeight(); j++) {
			auto& tile = newMap.getTile({i, j});
			auto position = Vec2u {i * tile.getDimensions().x,
			                       j * tile.getDimensions().y};
			tile.draw(position, target);
			tile.frameTick();
		}
	}
}

/*
 *  Rysowanie dekoracji świata, np. kwiaty na trawie, krzaki, itp.
 */
void Engine::RenderTilePass2(sf::RenderTarget&) {

}

/*
 *  Rysowanie elementów aktywnych świata. NPC, gracz, przedmioty na ziemi, ...
 */
void Engine::RenderEntity(sf::RenderTarget& target) {
	tempPlayer.draw(target);
}
