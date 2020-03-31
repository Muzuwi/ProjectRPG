#include "StatUI.hpp"

StatUI::StatUI() { }

void StatUI::DrawSelf(sf::RenderTarget& target) {
	title.setFont(font);
	title.setString("Character");
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(24);
	title.setPosition(sf::Vector2f(90.f, 25.f));
	target.draw(title);
}