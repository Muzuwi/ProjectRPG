#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Hud.hpp"
#include "StatUI.hpp"
#include "InvUI.hpp"
#include "SettUI.hpp"
#include "Window.hpp"

enum Scene {
	NONE,
	EQ,
	STATS,
	JOURNAL,
	SETTINGS,
	MAP
};

class GameUI {
private:
	Scene current;

	SettUI settings;
	StatUI stats;
	InvUI eq;
	Hud hud;
public:
	GameUI();

	void Init();
	void DrawGUI(sf::RenderTarget&,const int&, const int&, const int&, const int&);
	
	void SetScene(sf::Event::KeyEvent);
	void ProcessKey(sf::Event::KeyEvent);
	bool IsSceneKey(sf::Event::KeyEvent);
	bool IsActive();
};