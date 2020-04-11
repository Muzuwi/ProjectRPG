#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "AssetManager.hpp"
#include "Interface/Components/Frame.hpp"

enum ButtonType { //what inside?
	TEXT = 0,
	ICON = 1
};

class Button : public Frame{
protected:
	//Type of the button
	ButtonType type;

	sf::Text text;		//ButtonType = 0
	sf::Sprite icon;	//ButtonType = 1

	//Other
	unsigned int icon_index;	//icon index in graphic
	sf::Font font;				//font for text
	std::string source;			//name of file or string

	void SelfDraw(sf::RenderTarget&)override;
	void SelfInit()override;
public:
	Button(std::string, unsigned int);	//constructor of icon
	Button(std::string);				//constructor of text
};