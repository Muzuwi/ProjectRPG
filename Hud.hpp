#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include "Graphics/Spritesheet.hpp"

class Hud {
private:
	sf::Texture hudT, hpT, mpT;
	sf::Sprite hud, hp, mp;
public:
	Hud::Hud();

	void Hud::Init();
	void draw(sf::RenderTarget&, int, int, int, int);
};