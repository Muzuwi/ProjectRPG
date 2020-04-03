#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics/TextureManager.hpp"
#include "Interface/Frame.hpp"

class Button : public Frame{
protected:
	sf::Text text;
	sf::Font font;
	string content;

	void SelfDraw(sf::RenderTarget&)override;
	void SelfInit()override;
public:
	Button(string);
};