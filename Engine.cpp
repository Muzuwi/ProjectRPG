#include "Engine.h"

Engine::Engine() {

}

Engine::~Engine() {

}

bool Engine::Init() {
	window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Projekt");
	Camera* cam = new Camera(800, 600, 0.2f);
	LoadTextures();
	if (!window) return false;
	return true;
}

void Engine::LoadTextures() {
	sf::Texture sprite;
	
	sprite.loadFromFile("sprite1.png");
	textureManager.AddTexture(sprite);
	testTile = new Tile(textureManager.GetTexture(0));
}

void Engine::RenderFrame() {
	window->clear();
	testTile->Draw(30, 30, window);
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
	if (!Init()) throw "B³¹d w inicjalizacji silnika";
	MainLoop();
}