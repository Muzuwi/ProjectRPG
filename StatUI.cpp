#include "StatUI.hpp"

StatUI::StatUI() { }

void StatUI::Init() {
	UI = TextureManager::get()->getSpritesheet("statistics").getSprite();
}

void StatUI::draw(sf::RenderTarget& target) {
	target.draw(UI);
}