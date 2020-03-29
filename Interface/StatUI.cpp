#include "StatUI.hpp"

StatUI::StatUI() { }

void StatUI::Init() {
	UI = TextureManager::get()->getSpritesheet("left_panel").getSprite();

	font.loadFromFile("GameContent/Fonts/arial.ttf");
	title.setFont(font);

	title.setString("Statistics");
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(24);
	title.setPosition(sf::Vector2f(75.f, 20.f));
}

void StatUI::draw(sf::RenderTarget& target) {
	target.draw(UI);
	target.draw(title);
}