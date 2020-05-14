#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Interface/Hud.hpp"
#include "Interface/Inventory/InvUI.hpp"
#include "Interface/Settings/SettUI.hpp"
#include "Interface/Components/Window.hpp"

enum Scene {
	NONE,
	EQ,
	JOURNAL,
	SETTINGS,
	MAP
};

class GameUI {
private:
	Scene current;

	SettUI settings;
	InvUI eq;
	Hud hud;
	Player& player;
public:
	GameUI(Player& player);

	void Init();
	void DrawGUI(sf::RenderTarget&,const int&, const int&, const int&, const int&);
	
	void SetScene(sf::Event::KeyEvent);
	void ProcessKey(sf::Event::KeyEvent);
	bool IsSceneKey(sf::Event::KeyEvent);
	bool IsActive();
};