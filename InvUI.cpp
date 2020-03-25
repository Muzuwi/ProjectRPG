#include "InvUI.hpp"

InvUI::InvUI() { }

void InvUI::Init() {
	UI = TextureManager::get()->getSpritesheet("eq").getSprite();
	UI.setPosition(450, 0);
}

void InvUI::draw(sf::RenderTarget& target) {
	target.draw(UI);
}