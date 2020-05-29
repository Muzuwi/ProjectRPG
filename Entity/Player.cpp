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
//========== STATISTICS ==========//
	//HP
	statistics["HP"] = 85;
	statistics["MaxHP"] = 100;
	//MP
	statistics["MP"] = 12;
	statistics["MaxMP"] = 35;
	//Attack
		//Physical
	statistics["MinPhysical"] = 3;
	statistics["MaxPhysical"] = 5;
		//Magical
	statistics["MinMagical"] = 1;
	statistics["MaxMagical"] = 2;
		//Poison
	statistics["MinPoison"] = 0;
	statistics["MaxPoison"] = 0;
		//Other
	statistics["Crit"] = 3;
	statistics["Precision"] = 95; //%
	//Defence
	statistics["Armor"] = 2;
	statistics["Dodge"] = 10;
	//Resistances
	statistics["MagicalRes"] = 0;
	statistics["PoisonRes"] = 0;

//========== EXPERIENCE ==========//
	player_info["lvl"] = 8;
	player_info["current"] = 2321;
	player_info["next"] = 2656;
	player_info["gold"] = 352;
}

void Player::Lvlup() {
	if(player_info["lvl"] < 30) player_info["lvl"] += 1;	//temporary cap: 30 lvl
	player_info["current"] = 0;
	player_info["next"] += (int)(player_info["next"] * (5.2 / player_info["lvl"]));
	std::cout << "LvL: " << player_info["lvl"] << " -> " << player_info["next"] << std::endl;
}