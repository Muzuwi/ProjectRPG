#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Tile.h"
#include "Camera.h"
#include "Map.h"

class Engine
{
private:
	sf::RenderWindow* window;
	Tile* testTile;

	TextureManager textureManager;
	Map* currentMap;

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

