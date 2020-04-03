#include "Button.hpp"

Button::Button(string title) : content(title), Frame(){ }

void Button::SelfInit() {
	font.loadFromFile("GameContent/Fonts/arial.ttf");
	text.setFont(font);

	text.setString(content);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(20);
	text.setPosition(position.x + 5, position.y + 5);	//to add responding shift based on size of button
}


void Button::SelfDraw(sf::RenderTarget& target) {
	target.draw(text);
}