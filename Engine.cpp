#include <memory>
#include "Engine.hpp"

Engine::Engine() {

}

Engine::~Engine() {

}

bool Engine::Init() {
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(windowWidth, windowHeight, 32), "Projekt");
	if (!window) return false;
	window->setFramerateLimit(60);

	LoadTextures();
	GUI.Init();
	world.loadMap("");

	if(!mapTexture.create(world.getMap().getWidth() * Tile::dimensions().x, world.getMap().getHeight() * Tile::dimensions().y))
		return false;

	return true;
}

void Engine::LoadTextures() {
	textureManager.autoload();
}

void Engine::RenderFrame() {
	window->clear();

	RenderTile(mapTexture);
	RenderEntity(mapTexture);

	mapTexture.display();

	auto player = world.getPlayer();
	auto playerCentre = player.getSpritePosition() + Vec2f(player.getDimensions()/2u);
	Vec2f viewCenter = playerCentre;
	if(playerCentre.x + (windowWidth/2.0f) > mapTexture.getSize().x)
		viewCenter.x = mapTexture.getSize().x - (windowWidth/2.0f);
	if(playerCentre.y + (windowHeight/2.0f) > mapTexture.getSize().y)
		viewCenter.y = mapTexture.getSize().y - (windowHeight/2.0f);
	if(playerCentre.x - (windowWidth/2.0f) < 0)
		viewCenter.x = (windowWidth/2.0f);
	if(playerCentre.y - (windowHeight/2.0f) < 0)
		viewCenter.y = (windowHeight/2.0f);

	sf::View view(viewCenter, Vec2f(windowWidth, windowHeight));
	window->setView(view);
	window->draw(sf::Sprite(mapTexture.getTexture()));

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

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) world.movePlayer(Direction::Up);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) world.movePlayer(Direction::Down);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) world.movePlayer(Direction::Left);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) world.movePlayer(Direction::Right);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) GUI.SetScene(event.key);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) GUI.SetScene(event.key);
}

void Engine::Update() {
	world.getPlayer().update();
}

void Engine::MainLoop() {
	while (window->isOpen()) {
		ProcessInput();
		Update();
		RenderFrame();
	}
}

void Engine::Start() {
	if (!Init()) throw std::runtime_error("Engine has failed to initialize!");
	MainLoop();
}

/*
 *  Rysowanie wszystkich kafelek/ziemi oraz dekoracji świata, np. kwiaty na trawie, krzaki, itp.
 */
void Engine::RenderTile(sf::RenderTarget& target) {
	world.getMap().draw(target);
}

/*
 *  Rysowanie elementów aktywnych świata. NPC, gracz, przedmioty na ziemi, ...
 */
void Engine::RenderEntity(sf::RenderTarget& target) {
	world.getPlayer().draw(target);
}


void Engine::RenderHud(sf::RenderTarget& target) {
	int HP = world.getPlayer().getHP();
	int MP = world.getPlayer().getMP();
	int maxHP = world.getPlayer().getMaxHP();
	int maxMP = world.getPlayer().getMaxMP();
	GUI.DrawGUI(target, HP, MP, maxHP, maxMP);
}