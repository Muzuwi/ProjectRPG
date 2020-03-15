#include "TextureManager.h"
#include "Tile.hpp"

void Tile::draw(Vec2u position, sf::RenderTarget& target) {
	sf::Sprite sprite(TextureManager::get()->GetTexture(tileType));
	sprite.setPosition(sf::Vector2f{static_cast<float>(position.x), static_cast<float>(position.y)});
	target.draw(sprite);
}

Vec2u Tile::getDimensions() const {
	return {32, 32};
}
