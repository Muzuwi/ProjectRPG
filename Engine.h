#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Map.hpp"
#include "Entity/Player.h"

class Engine
{
private:
	const unsigned windowWidth = 800;
	const unsigned windowHeight = 600;

	std::shared_ptr<sf::RenderWindow> window;

	TextureManager textureManager;
//	OverworldManager overworld;

	Map newMap;

	Player tempPlayer;

	void RenderTile(sf::RenderTarget&);
	void RenderTilePass2(sf::RenderTarget&);
	void RenderEntity(sf::RenderTarget&);

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

