#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "World/WorldManager.hpp"
#include "Graphics/TextureManager.hpp"
#include "Interface/Hud.hpp"
#include "Interface/GameUI.hpp"
#include "Sound/SoundEngine.hpp"

class Engine
{
private:
	const unsigned windowWidth = 800;
	const unsigned windowHeight = 600;

	std::shared_ptr<sf::RenderWindow> window;
	sf::RenderTexture mapTexture;

	WorldManager world;
	SoundEngine soundEngine;
	GameUI GUI;

	void RenderWorld(sf::RenderTarget&);
	void RenderHud(sf::RenderTarget&);

	bool Init();
	void MainLoop();
	void RenderFrame();
	void ProcessInput();
	void Update();

public:
	Engine() {};
	~Engine() {};

	void Start();
};

