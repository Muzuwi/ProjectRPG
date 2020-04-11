#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Interface/Window.hpp"

class StatUI : public Window {
private:
	sf::Text title;

public:
	StatUI();
	void DrawSelf(sf::RenderTarget&);
};