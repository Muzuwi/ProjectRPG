#include "Button.hpp"

Button::Button(string file, string name, int n1, int n2)
	: file_name(file), text_name(name), x(n1), y(n2), focus(false) { }

void Button::Init() {


	button = TextureManager::get()->getSpritesheet(file_name).getSprite();
	button.setPosition(x, y);

	font.loadFromFile("GameContent/Fonts/arial.ttf");
	text.setFont(font);

	text.setString(text_name);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(20);
	text.setPosition(x + 10, y);	//to add responding shift based on size of button
}

void Button::draw(sf::RenderTarget& target) {
	target.draw(button);
	target.draw(text);
}

void Button::SetFocus() { 
	string sufix = "_focus";
	string temp = file_name + sufix;
	button = TextureManager::get()->getSpritesheet(temp).getSprite();
	button.setPosition(x, y);
	focus = true; 
}
void Button::RemoveFocus() { 
	button = TextureManager::get()->getSpritesheet(file_name).getSprite();
	button.setPosition(x, y);
	focus = false; 
}