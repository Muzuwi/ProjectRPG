#include "World/Tile.hpp"
#include "Graphics/TextureManager.hpp"
#include "NPC.hpp"

void NPC::onMove(Direction) { }
void NPC::onUpdate() { }
void NPC::onInteract(Direction dir) {
	facing = dir;
	std::cout << "I was interacted with!\n";
}
void NPC::onStep() { }
void NPC::frameTick() { }

void NPC::draw(sf::RenderTarget &target) {
	sf::Sprite sprite;
	switch(facing) {
		case Direction::Up:
			sprite = spritesheet.get().getSprite(3, isMoving ? (frameCounter / movementSpeed) % 4 : 0 );
			break;
		case Direction::Down:
			sprite = spritesheet.get().getSprite(0, isMoving ? (frameCounter / movementSpeed) % 4: 0 );
			break;
		case Direction::Left:
			sprite = spritesheet.get().getSprite(1, isMoving ? (frameCounter / movementSpeed) %4: 0 );
			break;
		case Direction::Right:
			sprite = spritesheet.get().getSprite(2, isMoving ? (frameCounter / movementSpeed) %4: 0 );
			break;
		default: break;
	}

	Vec2f drawPosition = spritePosition - Vec2f((getDimensions().x - Tile::dimensions()) / 2, getDimensions().y - Tile::dimensions());
	sprite.setPosition(drawPosition);
	target.draw(sprite);
}

Vec2u NPC::getDimensions() const {
	return spritesheet.get().getSpriteSize();
}

NPC::NPC(const std::string &texture, Vec2u worldPos)
: Actor(1, 5, worldPos), spritesheet(TextureManager::get()->getSpritesheet(texture))
{
	spritesheet = TextureManager::get()->getSpritesheet(texture);
}
