#include "InvUI.hpp"

InvUI::InvUI() { }

void InvUI::Init() {
	UI = TextureManager::get()->getSpritesheet("right_panel").getSprite();
	UI.setPosition(450, 0);

	font.loadFromFile("GameContent/fonts/arial.ttf");
	title.setFont(font);

	title.setString("Equipment");
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(24);
	title.setPosition(sf::Vector2f(610.f, 20.f));
}

void InvUI::draw(sf::RenderTarget& target) {
	target.draw(UI);
	target.draw(title);
}