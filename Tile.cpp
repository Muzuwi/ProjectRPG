#include "TextureManager.hpp"
#include "Tile.hpp"

void Tile::draw(Vec2u position, sf::RenderTarget& target) {
	switch(tileType) {
		case 0:
		case 1: {
			auto sprite = TextureManager::get()->getSpritesheet(tileType ? "sprite2" : "sprite1").getSprite();
			sprite.setPosition(sf::Vector2f{static_cast<float>(position.x), static_cast<float>(position.y)});
			target.draw(sprite);
			break;
		}

		case 2: {
			auto textureframe = this->frame / (16*30);
			auto sprite = TextureManager::get()->getSpritesheet("spritesheets").getSprite(0, textureframe);
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