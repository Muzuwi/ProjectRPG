#include "Item.hpp"

Item::Item(string n, string q, string t, string v, vector<string> s, vector<string> d)
	: name(n), quality(q), type(type), value(v), stats(s), description(d) {
	statLines = stats.size();
	descLines = description.size();
}

void Item::Init(string name) {
	sprite.setTexture(TextureManager::get()->getSpritesheet(name).getTexture());
}

void Item::Draw(sf::Vector2f position, sf::RenderWindow& target) {
	sprite.setPosition(position);
	target.draw(sprite);
}