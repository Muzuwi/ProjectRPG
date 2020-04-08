#include "Item.hpp"

Item::Item(string n, string q, string t, string v, string s, string d)
	: name(n), quality(q), type(t), value(v), stats(s), description(d) { }

void Item::Init(string name) {
	sprite.setTexture(TextureManager::get()->getSpritesheet(name).getTexture());
}

void Item::Draw(sf::Vector2f position, sf::RenderTarget& target) {
	sprite.setPosition(position);
	target.draw(sprite);
}