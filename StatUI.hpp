#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include "Graphics/Spritesheet.hpp"

class StatUI {
private:
	sf::Sprite UI;

public:
	StatUI();
	void Init();
	void draw(sf::RenderTarget&);
};