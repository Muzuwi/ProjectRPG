#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "World/WorldManager.hpp"
#include "AssetManager.hpp"
#include "Interface/Hud.hpp"
#include "Interface/GameUI.hpp"
#include "Sound/SoundEngine.hpp"
#include "Interface/DialogEngine.hpp"
#include "BattleSystem/BattleEngine.hpp"

enum Focus{
	INGAME = 0,
	INTERFACE = 1,
	BATTLE = 2,
	DIALOG = 3
};

class Engine
{
private:
	unsigned windowWidth = 800;
	unsigned windowHeight = 600;

	std::shared_ptr<sf::RenderWindow> window;

	Focus scene;

	WorldManager world;
	SoundEngine soundEngine;
	DialogEngine dialogEngine;
	GameUI GUI;
	BattleEngine battleEngine;

	void RenderWorld(sf::RenderTarget&);
	void RenderHud(sf::RenderTarget&);

	bool Init();
	void MainLoop();
	void RenderFrame();
	void ProcessInput();
	void Update();

public:
	Engine()
	: GUI(world.getPlayer()), battleEngine(world.getPlayer()){};

	~Engine() {};

	void Start();
	//static void ResizeWindow(std::shared_ptr<sf::RenderWindow>, std::pair<unsigned int, unsigned int>);
};

