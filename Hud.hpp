#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include "Graphics/Spritesheet.hpp"

class Hud {
public:
	Hud();

	void draw(sf::RenderTarget&, int, int, int, int);
};