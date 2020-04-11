#include "Button.hpp"

Button::Button(std::string s) : type(TEXT), source(s), Frame(){ 
	
}

Button::Button(std::string s, unsigned int index) : type(ICON), source(s), icon_index(index), Frame() {

}

void Button::SelfInit() {
	if (type == TEXT) {
		font.loadFromFile("GameContent/Fonts/arial.ttf");
		text.setFont(font);
		text.setString(source);
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(20);
		sf::Vector2f stringSize = (text.findCharacterPos(source.size()) - text.findCharacterPos(0));
		text.setPosition(position + sf::Vector2f(size.x / 2, 0) - sf::Vector2f(stringSize.x / 2, 0));
	}
	if (type == ICON) {
		icon = AssetManager::getUI(source).getSprite();
		icon.setTextureRect(sf::IntRect(32 * icon_index, 0, 32, 32));
		icon.setPosition(position + sf::Vector2f(2, 2));
	}
}


void Button::SelfDraw(sf::RenderTarget& target) {
	if (type == TEXT) {
		target.draw(text);
	}
	if (type == ICON) {
		target.draw(icon);
	}
}