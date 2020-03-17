#include "TextureManager.h"
#include "Player.h"

void Player::draw(sf::RenderTarget &target) {
	Vec2f drawPosition {0, 0};

	auto playerTilePos = Vec2u(worldPosition / 32.0f);
	auto temp = (target.getSize() / 32u);
	auto centerTile = (temp / 2u);

	if(playerTilePos.x > centerTile.x) {
		drawPosition.x = centerTile.x * 32.0f;
	}
	else
		drawPosition.x = worldPosition.x;

	if(playerTilePos.y > centerTile.y) {
		drawPosition.y = centerTile.y * 32.0f;
	} else
		drawPosition.y = worldPosition.y;

	sf::RectangleShape shape;
	shape.setPosition(Vec2f(centerTile) * 32.0f);
	shape.setSize(Vec2f{32, 32});
	shape.setFillColor(sf::Color::Red);
	target.draw(shape);

	auto sprite = TextureManager::get()->getSpritesheet("playersprite.png").getSprite();
	sprite.setPosition(drawPosition);
	target.draw(sprite);
}

Vec2u Player::getDimensions() const {
	return {32,64};
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
