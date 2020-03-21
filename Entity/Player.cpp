#include "TextureManager.hpp"
#include "Player.hpp"

void Player::draw(sf::RenderTarget &target) {
	sf::Sprite sprite;
	switch(facing) {
		case Direction::Up:
			sprite = TextureManager::get()->getSpritesheet("playersprite.png").getSprite(3, isMoving ? (frameCounter / movementSpeed) % 4 : 0 );
			break;
		case Direction::Down:
			sprite = TextureManager::get()->getSpritesheet("playersprite.png").getSprite(0, isMoving ? (frameCounter / movementSpeed) % 4: 0 );
			break;
		case Direction::Left:
			sprite = TextureManager::get()->getSpritesheet("playersprite.png").getSprite(1, isMoving ? (frameCounter / movementSpeed) %4: 0 );
			break;
		case Direction::Right:
			sprite = TextureManager::get()->getSpritesheet("playersprite.png").getSprite(2, isMoving ? (frameCounter / movementSpeed) %4: 0 );
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
	if(worldPosition.x != spritePosition.x) {
		double delta = spritePosition.x - worldPosition.x;
		if(delta < 0) {
			spritePosition.x += (double)movementSpeed;
			if(spritePosition.x >= worldPosition.x) {
				spritePosition.x = worldPosition.x;
				isMoving = false;
			}
		} else {
			spritePosition.x -= (double)movementSpeed;
			if(spritePosition.x <= worldPosition.x) {
				spritePosition.x = worldPosition.x;
				isMoving = false;
			}
		}
	} else if(worldPosition.y != spritePosition.y) {
		double delta = spritePosition.y - worldPosition.y;
		if(delta < 0) {
			spritePosition.y += (double)movementSpeed;
			if(spritePosition.y >= worldPosition.y) {
				spritePosition.y = worldPosition.y;
				isMoving = false;
			}
		} else {
			spritePosition.y -= (double)movementSpeed;
			if(spritePosition.y <= worldPosition.y) {
				spritePosition.y = worldPosition.y;
				isMoving = false;
			}
		}

	}
}

void Player::move(Direction dir) {
	if(worldPosition != spritePosition) return;

	switch(dir) {
		case Direction::Up: this->worldPosition.y -= 32; isMoving = true; break;
		case Direction::Down: this->worldPosition.y += 32; isMoving = true;  break;
		case Direction::Left: this->worldPosition.x -= 32; isMoving = true;  break;
		case Direction::Right: this->worldPosition.x += 32; isMoving = true;  break;
		default: break;
	}

	facing = dir;
}

void Player::go_to(Vec2f) {

}
