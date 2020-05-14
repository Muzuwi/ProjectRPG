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

void Player::setDefaultStatistics() {
	//HP
	statistics["HP"] = 85;
	statistics["MaxHP"] = 100;
	//MP
	statistics["MP"] = 12;
	statistics["MaxMP"] = 35;
	//Attack
	statistics["Crit"] = 3;
	statistics["Precision"] = 95; //%
		//Physical
	statistics["MinPhysical"] = 3;
	statistics["MaxPhysical"] = 5;
		//Fire
	statistics["MinFire"] = 0;
	statistics["MaxFire"] = 0;
		//Ice
	statistics["MinIce"] = 0;
	statistics["MaxIce"] = 0;
		//Thunder
	statistics["MinThunder"] = 0;
	statistics["MaxThunder"] = 0;
		//Poison
	statistics["MinPoison"] = 0;
	statistics["MaxPoison"] = 0;
	//Defence
	statistics["Armor"] = 2;
	statistics["Dodge"] = 10;
	//Resistances
	statistics["FireRes"] = 0;
	statistics["IceRes"] = 0;
	statistics["ThunderRes"] = 0;
	statistics["PoisonRes"] = 0;
	//Atributes
	statistics["Strength"] = 11;
	statistics["Vitality"] = 8;
	statistics["Agility"] = 6;
	statistics["Intelligence"] = 2;
}