#include "World/Tile.hpp"
#include "AssetManager.hpp"
#include "Player.hpp"

Player* Player::instance {nullptr};

Player::Player()
: Actor(0, 4) {
	instance = this;
	this->loadFromSavegame();
}

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
	statistics["Attack"] = 3;		//Physical Attack
	statistics["Fire"] = 0;			//Fire Power
	statistics["Water"] = 0;		//Water Power
	statistics["Lightning"] = 0;	//Lightning Power
	//Defence
	statistics["AttackSpeed"] = 2;
	statistics["Armor"] = 1;
	statistics["Resistance"] = 0;
	//Other
	statistics["Critical"] = 0;		//%
	statistics["Dodge"] = 0;
	

//========== EXPERIENCE ==========//
	player_info["lvl"] = 1;
	player_info["current"] = 0;
	player_info["next"] = 11;
	player_info["gold"] = 25;

	auto save = AssetManager::getSavefile();
	save.set("playerStats", statistics);
	save.set("playerInfo", player_info);
	save.saveToFile();
}

void Player::Lvlup() {
	if (player_info["lvl"] < 30) {	//temporary cap: 30 lvl
		player_info["lvl"] += 1;
		player_info["current"] = 0;
		player_info["next"] += (int)(player_info["next"] * (5.2 / player_info["lvl"]));
		statistics["MaxHP"] += (int)(statistics["MaxHP"] * (2.3 / player_info["lvl"]));
		statistics["MaxMP"] += (int)(statistics["MaxMP"] * (2.1 / player_info["lvl"]));
		statistics["HP"] = statistics["MaxHP"];
		statistics["MP"] = statistics["MaxMP"];
	}
}

void Player::GainEXP(int amount) {
	player_info["current"] += amount;
	while(player_info["current"] >= player_info["next"]) {
		int overflow = player_info["current"] - player_info["next"];
		Lvlup();
		player_info["current"] += overflow;
	}
}

void Player::GainGold(int amount) {
	player_info["gold"] += amount;
	if (player_info["gold"] > 9999) player_info["gold"] = 9999;
}

void Player::setPosition(Vec2u worldPos) {
	isMoving = false;
	worldPosition = worldPos;
	spritePosition = Vec2f(worldPos * Tile::dimensions());
}

void Player::saveToSavegame() {
	inventory.saveToSavegame();

	auto save = AssetManager::getSavefile();
	save.set("playerStats", statistics);
	save.set("playerInfo", player_info);
}

void Player::loadFromSavegame() {
	auto save = AssetManager::getSavefile();

	if (save.exists("playerName"))
		name = save.get<std::string>("playerName");
	else name = "Andrzej";

	if(save.exists("playerStats") && save.exists("playerInfo")) {
		statistics = save.get<std::map<std::string, int>>("playerStats");
		player_info = save.get<std::map<std::string, int>>("playerInfo");
	} else {
		setDefaultStatistics();
	}

	if(save.exists("playerCurrentPos"))
		setPosition(save.get<Vec2u>("playerCurrentPos"));
}