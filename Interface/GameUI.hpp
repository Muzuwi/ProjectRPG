#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Hud.hpp"
#include "StatUI.hpp"
#include "InvUI.hpp"

enum Scene {
	NONE,
	EQ,
	STATS,
	JOURNAL,
	SETTINGS,
	MAP,
	MAINMENU
};

class GameUI {
private:
	Scene left;
	Scene right;

	StatUI stats;
	InvUI eq;
	Hud hud;
public:
	GameUI();

	void Init();
	void DrawGUI(sf::RenderTarget&,const int&, const int&, const int&, const int&);
	void SetScene(sf::Event::KeyEvent);
};