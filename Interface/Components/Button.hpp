#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "AssetManager.hpp"
#include "Interface/Components/Frame.hpp"

class Button : public Frame{
protected:
	sf::Text text;
	sf::Font font;
	std::string content;

	void SelfDraw(sf::RenderTarget&)override;
	void SelfInit()override;
public:
	Button(std::string);
};