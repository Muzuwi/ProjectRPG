#include "Hud.hpp"

void Hud::Init() {
	hp = AssetManager::getUI("hp_fill").getSprite();
	mp = AssetManager::getUI("mp_fill").getSprite();
	base = AssetManager::getUI("hud_cover").getSprite();
	exp = AssetManager::getUI("hud_exp").getSprite();
	back = AssetManager::getUI("hud_back").getSprite();

	base.setPosition(position);
	hp.setPosition(position);
	mp.setPosition(position);
	exp.setPosition(position);
	back.setPosition(position);
}

void Hud::Draw(sf::RenderTarget& target) {
	if (player.getWorldPosition().x > 10 or player.getWorldPosition().y > 3) {

		target.draw(back);
		float shiftHP = 320 * (player.getStatistics()["HP"] / double(player.getStatistics()["MaxHP"]));
		float shiftMP = 320 * (player.getStatistics()["MP"] / double(player.getStatistics()["MaxMP"]));
		float shiftExp = (player.getPlayerInfo()["current"] / double(player.getPlayerInfo()["next"]));

		hp.setTextureRect(sf::IntRect(0, 0, shiftHP, 18));
		hp.setPosition(position + sf::Vector2f(86, 18));
		target.draw(hp);

		mp.setTextureRect(sf::IntRect(0, 0, shiftMP, 18));
		mp.setPosition(position + sf::Vector2f(86, 52));
		target.draw(mp);

		exp.setTextureRect(sf::IntRect(0, 128 - 128*shiftExp, 128, 128*shiftExp));
		exp.setPosition(position + sf::Vector2f(0, 128 - 128 * shiftExp));
		target.draw(exp);

		target.draw(base);

		DrawLine(target, position + sf::Vector2f(230, 18), ParseStatistic("", player.getStatistics()["HP"], "/", player.getStatistics()["MaxHP"], "", 16));
		DrawLine(target, position + sf::Vector2f(230, 52), ParseStatistic("", player.getStatistics()["MP"], "/", player.getStatistics()["MaxMP"], "", 16));
		DrawLine(target, position + sf::Vector2f(32, 28), ParseStatistic("lvl", player.getPlayerInfo()["lvl"], "", 24));
		DrawLine(target, position + sf::Vector2f(48, 72), ParseStatistic("", shiftExp*100, " %", 16));
		DrawLine(target, position + sf::Vector2f(158, 86), ParseStatistic("", player.getPlayerInfo()["gold"], "", 16));
	}
}

sf::Text Hud::ParseStatistic(std::string prefix, int value1, std::string separator, int value2, std::string sufix, int fontSize) {
	std::string line = prefix + std::to_string(value1) + separator + std::to_string(value2) + sufix;
	return sf::Text(line, font, fontSize);
}

sf::Text Hud::ParseStatistic(std::string prefix, int value, std::string sufix, int fontSize) {
	std::string line = prefix + std::to_string(value) + sufix;
	return sf::Text(line, font, fontSize);
}

void Hud::DrawLine(sf::RenderTarget& target, sf::Vector2f position, sf::Text text) {
	text.setFont(font);
	text.setColor(sf::Color::White);
	text.setPosition(position);
	target.draw(text);
}