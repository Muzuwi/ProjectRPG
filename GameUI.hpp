#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Hud.hpp"

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
	Hud hud;
public:
	GameUI();

	void Init();
	void DrawGUI(sf::RenderTarget&,const int&, const int&, const int&, const int&);
};