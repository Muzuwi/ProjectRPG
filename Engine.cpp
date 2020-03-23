#include <memory>
#include "Engine.hpp"

Engine::Engine() {

}

Engine::~Engine() {

}

bool Engine::Init() {
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(windowWidth, windowHeight, 32), "Projekt");
	window->setFramerateLimit(60);
	newMap = Map::from_file("");
	LoadTextures();
	if (!window) return false;
	return true;
}

void Engine::LoadTextures() {
	textureManager.autoload();
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

	auto playerCentre = tempPlayer.getSpritePosition() + Vec2f(tempPlayer.getDimensions()/2u);
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
	window->setView(window->getDefaultView());
	RenderHud(*window);
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
			default: break;
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) tempPlayer.move(Direction::Up);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) tempPlayer.move(Direction::Down);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) tempPlayer.move(Direction::Left);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) tempPlayer.move(Direction::Right);
}

void Engine::Update() {
	tempPlayer.update();
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

void Engine::RenderHud(sf::RenderTarget& target) {
	int HP = tempPlayer.getHP();
	int MP = tempPlayer.getMP();
	int maxHP = tempPlayer.getMaxHP();
	int maxMP = tempPlayer.getMaxMP();
	gameHud.draw(target, HP, MP, maxHP, maxMP);
}