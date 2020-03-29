#include "SettUI.hpp"

SettUI::SettUI() { }

void SettUI::Init() {
	UI = TextureManager::get()->getSpritesheet("settings").getSprite();
	UI.setPosition(sf::Vector2f(250.f, 100.f));

	font.loadFromFile("GameContent/fonts/arial.ttf");
	title.setFont(font);

	title.setString("Settings");
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(24);
	title.setPosition(sf::Vector2f(355.f, 130.f));
}

void SettUI::draw(sf::RenderTarget& target) {
	target.draw(UI);
	target.draw(title);
}