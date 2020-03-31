#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Interface/Window.hpp"

class StatUI : public Window {
private:
	sf::Text title;

public:
	StatUI();
	void DrawSelf(sf::RenderTarget&);
};