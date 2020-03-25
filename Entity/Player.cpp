#include "Tile.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"

void Player::draw(sf::RenderTarget &target) {
	sf::Sprite sprite;
	switch(facing) {
		case Direction::Up:
			sprite = TextureManager::get()->getSpritesheet("playersprite").getSprite(3, isMoving ? (frameCounter / movementSpeed) % 4 : 0 );
			break;
		case Direction::Down:
			sprite = TextureManager::get()->getSpritesheet("playersprite").getSprite(0, isMoving ? (frameCounter / movementSpeed) % 4: 0 );
			break;
		case Direction::Left:
			sprite = TextureManager::get()->getSpritesheet("playersprite").getSprite(1, isMoving ? (frameCounter / movementSpeed) %4: 0 );
			break;
		case Direction::Right:
			sprite = TextureManager::get()->getSpritesheet("playersprite").getSprite(2, isMoving ? (frameCounter / movementSpeed) %4: 0 );
			break;
		default: break;
	}
	sprite.setPosition(spritePosition);
	target.draw(sprite);
}

Vec2u Player::getDimensions() const {
	return {32,48};
}

void Player::onInteract() {

}

void Player::onStep() {

}

bool Player::collisionCheck(Actor&) {
	return false;
}

void Player::update() {
	++frameCounter;

	if(isMoving) {
		auto targetPosition = Vec2u(worldPosition.x * Tile::dimensions().x,
									worldPosition.y * Tile::dimensions().y);
		if(targetPosition.x != spritePosition.x) {
			if(targetPosition.x > spritePosition.x) {
				spritePosition.x += (double)movementSpeed;
				if(spritePosition.x >= targetPosition.x) {
					spritePosition.x = targetPosition.x;
					isMoving = false;
				}
			} else {
				spritePosition.x -= (double)movementSpeed;
				if(spritePosition.x <= targetPosition.x) {
					spritePosition.x = targetPosition.x;
					isMoving = false;
				}
			}
		} else if(targetPosition.y != spritePosition.y) {
			if(targetPosition.y > spritePosition.y) {
				spritePosition.y += (double)movementSpeed;
				if(spritePosition.y >= targetPosition.y) {
					spritePosition.y = targetPosition.y;
					isMoving = false;
				}
			} else {
				spritePosition.y -= (double)movementSpeed;
				if(spritePosition.y <= targetPosition.y) {
					spritePosition.y = targetPosition.y;
					isMoving = false;
				}
			}

		}

	}
}

void Player::move(Direction dir) {
	if(isMoving) return;

	switch(dir) {
		case Direction::Up:     --this->worldPosition.y; isMoving = true;  break;
		case Direction::Down:   ++this->worldPosition.y; isMoving = true;  break;
		case Direction::Left:   --this->worldPosition.x; isMoving = true;  break;
		case Direction::Right:  ++this->worldPosition.x; isMoving = true;  break;
		default: break;
	}

	facing = dir;
}

void Player::go_to(Vec2f) {

}
