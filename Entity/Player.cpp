#include "TextureManager.h"
#include "Player.h"

void Player::draw(sf::RenderTarget &target) {
	auto sprite = TextureManager::get()->getSpritesheet("playersprite.png").getSprite();
	sprite.setPosition(worldPosition);
	target.draw(sprite);
}

Vec2u Player::getDimensions() const {
	return {32,48};
}

void Player::handleKeyboardEvent(bool pressed, sf::Event::KeyEvent& event) {
	if(pressed) {
		if(event.code == sf::Keyboard::W) this->worldPosition.y -= 32;
		else if(event.code == sf::Keyboard::S) this->worldPosition.y += 32;
		else if(event.code == sf::Keyboard::A) this->worldPosition.x -= 32;
		else if(event.code == sf::Keyboard::D) this->worldPosition.x += 32;
	}
}

void Player::onInteract() {

}

void Player::onStep() {

}

bool Player::collisionCheck(WorldEntity &entity) {
	return false;
}

void Player::update() {

}
