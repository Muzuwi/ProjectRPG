#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"
#include "Graphics/Spritesheet.hpp"
#include "Entity/Player.hpp"

class Hud {
private:
	sf::Sprite hp, mp, base, cricleL, cricleR;

public:
	Hud();
	void Init();
	void draw(sf::RenderTarget&, int, int, int, int);
};