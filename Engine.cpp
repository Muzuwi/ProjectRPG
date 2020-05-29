#include <memory>
#include "Engine.hpp"
#include "World/Item.hpp"

bool Engine::Init() {
	AssetManager::loadMaps();
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(windowWidth, windowHeight, 32), "Projekt");
	if (!window) return false;
	window->setFramerateLimit(60);
	
	scene = INGAME;
	GUI.Init(window);
	world.setCurrentMap("default");

	Item item {"sword", 1};

	world.getPlayer().getInventory().addItem(item);
	world.getPlayer().getInventory().addItem(item);
	world.getPlayer().getInventory().addItem({"coin", 40});
	world.getPlayer().getInventory().addItem({"coin", 40});
	world.getPlayer().getInventory().addItem({"coin", 40});
	world.getPlayer().getInventory().addItem({"coin", 40});
	world.getPlayer().getInventory().addItem({"coin", 40});
	world.getPlayer().getInventory().addItem({"sandaly", 1});
	world.getPlayer().getInventory().addItem({"plaszcz", 1});
	world.getPlayer().getInventory().addItem({"pawez", 1});
	world.getPlayer().getInventory().addItem({"smieciogrzebki", 1});
	world.getPlayer().getInventory().addItem({"sword3", 1});

	return true;
}

void Engine::RenderFrame() {
	window->clear();

	auto player = world.getPlayer();
	auto& map = world.getMap();
	auto playerCentre = player.getSpritePosition() + Vec2f(player.getDimensions()/2u);
	Vec2f worldSize (map.getWidth() * Tile::dimensions(), map.getHeight() * Tile::dimensions());
	Vec2f viewCenter = playerCentre;
	Vec2f viewport = Vec2f(windowWidth, windowHeight);
	Vec2f viewportHalf (viewport / 2.0f);
	if(playerCentre.x + viewportHalf.x > worldSize.x)
		viewCenter.x = worldSize.x - viewportHalf.x;
	if(playerCentre.y + viewportHalf.y > worldSize.y)
		viewCenter.y = worldSize.y - viewportHalf.y;
	if(playerCentre.x - viewportHalf.x < 0)
		viewCenter.x = viewportHalf.x;
	if(playerCentre.y - viewportHalf.y < 0)
		viewCenter.y = viewportHalf.y;
	if(worldSize.x < viewport.x)
		viewCenter.x = worldSize.x / 2.0f;
	if(worldSize.y < viewport.y)
		viewCenter.y = worldSize.y / 2.0f;

	sf::View view(viewCenter, Vec2f(windowWidth, windowHeight));

	window->setView(view);
	RenderWorld(*window);

	window->setView(sf::View(sf::Rect(0.f, 0.f, (float)windowWidth, (float)windowHeight)));
	RenderHud(*window);

	dialogEngine.draw(*window);

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
			case sf::Event::Resized: {
				this->windowWidth = event.size.width;
				this->windowHeight = event.size.height;
				break;
			}

			case sf::Event::KeyPressed: {
				if (scene == INGAME) {
					if (event.key.code == sf::Keyboard::Space) {
						world.playerInteract();
						if(dialogEngine.isDialogPresent())  scene = DIALOG;
					}

					if (event.key.code == sf::Keyboard::C ||
						event.key.code == sf::Keyboard::I ||
						event.key.code == sf::Keyboard::Escape) {
							scene = INTERFACE;
							GUI.ProcessKey(event.key);
					}
				}
				else if (scene == INTERFACE) {
					GUI.ProcessKey(event.key);
					if (!GUI.IsActive()) scene = INGAME;
				} else if (scene == DIALOG) {
					dialogEngine.handleKeyEvent(event.key);
					if(!dialogEngine.isDialogPresent()) scene = INGAME;
				}
			}
			default: break;
		}
	}
	if (scene == INGAME) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) world.movePlayer(Direction::Up);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) world.movePlayer(Direction::Down);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) world.movePlayer(Direction::Left);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) world.movePlayer(Direction::Right);
	}
}

void Engine::Update() {
	world.updateWorld();
	soundEngine.update();
	dialogEngine.update();
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
 *  Rysowanie elementów aktywnych świata. NPC, gracz, przedmioty na ziemi, ...
 */
void Engine::RenderWorld(sf::RenderTarget& target) {
	world.draw(target);
}

void Engine::RenderHud(sf::RenderTarget& target) {
	GUI.UpdateResolution(std::pair(windowWidth, windowHeight));
	GUI.DrawGUI(target);
}

//static void Engine::ResizeWindow(std::shared_ptr<sf::RenderWindow> window ,std::pair<unsigned int, unsigned int> resolution) {
//	window->setSize(sf::Vector2u(resolution.first, resolution.second));
//}