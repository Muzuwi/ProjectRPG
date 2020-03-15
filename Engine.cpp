#include <memory>
#include "Engine.h"

Engine::Engine() {

}

Engine::~Engine() {

}

bool Engine::Init() {
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600, 32), "Projekt");
	newMap = Map::from_file("");
	LoadTextures();
	if (!window) return false;
	return true;
}

void Engine::LoadTextures() {
	textureManager.AddTexture("sprite1.png");
	textureManager.AddTexture("sprite2.png");
}

void Engine::RenderFrame() {
	window->clear();

	for(unsigned i = 0; i < newMap.getWidth(); i++) {
		for(unsigned j = 0; j < newMap.getHeight(); j++) {
			auto& tile = newMap.getTile({i, j});
			tile.draw(Vec2u{i * tile.getDimensions().x,
				   j * tile.getDimensions().y}, *this->window);
		}
	}

	window->display();
}

void Engine::ProcessInput() {
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) window->close();
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