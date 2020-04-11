#include "Item.hpp"

Item::Item(std::string n, std::string q, std::string t, std::string v, std::string s, std::string d)
	: name(n), quality(q), type(t), value(v), stats(s), description(d) { }

void Item::Init(std::string name) {
	sprite.setTexture(AssetManager::getUI(name).getTexture());
}

void Item::Draw(sf::Vector2f position, sf::RenderTarget& target) {
	sprite.setPosition(position);
	target.draw(sprite);
}