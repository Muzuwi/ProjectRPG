#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"
#include "Graphics/Spritesheet.hpp"

class StatUI {
private:
	sf::Sprite UI;

public:
	StatUI();
	void Init();
	void draw(sf::RenderTarget&);
};