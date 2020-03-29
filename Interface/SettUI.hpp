#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"
#include "Graphics/Spritesheet.hpp"

class SettUI {
private:
	sf::Sprite UI;
	sf::Text title;
	sf::Font font;
public:
	SettUI();
	void Init();
	void draw(sf::RenderTarget&);
};