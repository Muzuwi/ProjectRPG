#include "World/Tile.hpp"
#include "AssetManager.hpp"
#include "NPC.hpp"
#include "Script.hpp"

void NPC::onMove(Direction) {
	actorScript->executeFunction("onMove");
}

void NPC::onUpdate() {
	actorScript->executeFunction("onUpdate");
}

void NPC::onInteract(Direction dir) {
	actorScript->executeFunction("onInteract", dir);
}

void NPC::onStep() {
	actorScript->executeFunction("onStep");
}

void NPC::draw(sf::RenderTarget &target) const {
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

NPC::NPC(const std::string &texture, Vec2u worldPos, const std::string& scrName)
: Actor(1, 5, worldPos), spritesheet(AssetManager::getCharacter(texture))
{
	spritesheetName = texture;
	scriptName = scrName;
	actorScript = std::make_shared<Script>(scrName);
	actorScript->set("npc", this);
}