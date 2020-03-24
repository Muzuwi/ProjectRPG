#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include "Map.hpp"
#include "Entity/Player.hpp"
#include "Hud.hpp"
#include "GameUI.hpp"

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
	GameUI GUI;

	void RenderTile(sf::RenderTarget&);
	void RenderTilePass2(sf::RenderTarget&);
	void RenderEntity(sf::RenderTarget&);
	void RenderHud(sf::RenderTarget&);

	bool Init();
	void MainLoop();
	void LoadTextures();
	void RenderFrame();
	void ProcessInput();
	void Update();

public:
	Engine();
	~Engine();

	void Start();
};

