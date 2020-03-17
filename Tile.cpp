#include <memory>
#include "TextureManager.h"
#include "Tile.hpp"

void Tile::draw(Vec2u position, sf::RenderTarget& target) {
	switch(tileType) {
		case 0:
		case 1: {
			sf::Sprite sprite(TextureManager::get()->GetTexture(tileType));
			sprite.setPosition(sf::Vector2f{static_cast<float>(position.x), static_cast<float>(position.y)});
			target.draw(sprite);
			break;
		}

		case 2: {
			auto textureframe = this->frame / (16*30);
			sf::Sprite sprite(TextureManager::get()->GetTexture(3 + textureframe));
			sprite.setPosition(sf::Vector2f{static_cast<float>(position.x), static_cast<float>(position.y)});
			target.draw(sprite);
		}

		default:
			break;
	}
}

Vec2u Tile::getDimensions() const {
	return {32, 32};
}