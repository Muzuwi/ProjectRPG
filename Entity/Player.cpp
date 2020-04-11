#include "World/Tile.hpp"
#include "AssetManager.hpp"
#include "Player.hpp"

void Player::draw(sf::RenderTarget &target) const {
	sf::Sprite sprite;
	switch(facing) {
		case Direction::Up:
			sprite = AssetManager::getCharacter("playersprite").getSprite(3, isMoving ? (frameCounter / movementSpeed) % 4 : 0 );
			break;
		case Direction::Down:
			sprite = AssetManager::getCharacter("playersprite").getSprite(0, isMoving ? (frameCounter / movementSpeed) % 4: 0 );
			break;
		case Direction::Left:
			sprite = AssetManager::getCharacter("playersprite").getSprite(1, isMoving ? (frameCounter / movementSpeed) %4: 0 );
			break;
		case Direction::Right:
			sprite = AssetManager::getCharacter("playersprite").getSprite(2, isMoving ? (frameCounter / movementSpeed) %4: 0 );
			break;
		default: break;
	}

	Vec2f drawPosition = spritePosition - Vec2f(0, getDimensions().y - Tile::dimensions());
	sprite.setPosition(drawPosition);
	target.draw(sprite);
}

Vec2u Player::getDimensions() const {
	return {32,48};
}