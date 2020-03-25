#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include "Graphics/Spritesheet.hpp"

class InvUI {
private:
	sf::Sprite UI;

public:
	InvUI();
	void Init();
	void draw(sf::RenderTarget&);
};

