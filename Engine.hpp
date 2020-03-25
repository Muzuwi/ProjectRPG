#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "World/WorldManager.hpp"
#include "TextureManager.hpp"
#include "Hud.hpp"
#include "GameUI.hpp"

class Engine
{
private:
	const unsigned windowWidth = 800;
	const unsigned windowHeight = 600;

	std::shared_ptr<sf::RenderWindow> window;
	sf::RenderTexture mapTexture;

	TextureManager textureManager;
	WorldManager world;

	GameUI GUI;

	void RenderTile(sf::RenderTarget&);
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

