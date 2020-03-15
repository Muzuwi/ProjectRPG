#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Map.hpp"

class Engine
{
private:
	std::shared_ptr<sf::RenderWindow> window;

	TextureManager textureManager;

	Map newMap;

	bool Init();
	void MainLoop();
	void LoadTextures();
	void RenderFrame();
	void ProcessInput();
	void Update();
	void LoadMap();
	
public:
	Engine();
	~Engine();

	void Start();
};

