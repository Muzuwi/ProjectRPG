#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"
#include "Graphics/Spritesheet.hpp"

class InvUI {
private:
	sf::Sprite UI;
	sf::Text title;
	sf::Font font;
public:
	InvUI();
	void Init();
	void draw(sf::RenderTarget&);
};

