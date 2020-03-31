#include "InvUI.hpp"

InvUI::InvUI() { }

void InvUI::DrawSelf(sf::RenderTarget& target) {
	title.setFont(font);
	title.setString("Inventory");
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(24);
	title.setPosition(sf::Vector2f(600.f, 25.f));
	target.draw(title);
}