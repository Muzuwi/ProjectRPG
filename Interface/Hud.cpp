#include "Hud.hpp"

void Hud::Init() {
	//Get textures
	hp = AssetManager::getUI("hp_fill").getSprite();
	mp = AssetManager::getUI("mp_fill").getSprite();
	base = AssetManager::getUI("hud").getSprite();
	exp = AssetManager::getUI("exp_fill").getSprite();

	//Set static Positions
	base.setPosition(position);
	hp.setPosition(position + sf::Vector2f(104, 45));
	mp.setPosition(position + sf::Vector2f(104, 66));

	//Static values - sizes of sections(from files)
	size = sf::Vector2f(420, 128);
	exp_size = sf::Vector2f(52, 101);
	bars_size = sf::Vector2f(287,8);
	main_section_size = sf::Vector2f(120, 120);
}

void Hud::Draw(sf::RenderTarget& target) {
	if (player.getWorldPosition().x > 12 or player.getWorldPosition().y > 3) {	//Hide HUD if player is obscured

		//Draw Base
		target.draw(base);

		//Calculate shifts
		float shiftHP = bars_size.x * (player.getStatistics()["HP"] / double(player.getStatistics()["MaxHP"]));
		float shiftMP = bars_size.x * (player.getStatistics()["MP"] / double(player.getStatistics()["MaxMP"]));
		float shiftExp = (player.getPlayerInfo()["current"] / double(player.getPlayerInfo()["next"]));

		//Draw HP Baar
		hp.setTextureRect(sf::IntRect(0, 0, shiftHP, 8));
		target.draw(hp);

		//Draw MP Bar
		mp.setTextureRect(sf::IntRect(0, 0, shiftMP, 8));
		target.draw(mp);

		//Cut and draw Exp Bar
		exp.setTextureRect(sf::IntRect(0, exp_size.y - exp_size.y *shiftExp, exp_size.x, exp_size.y *shiftExp));
		exp.setPosition(position + sf::Vector2f(0, exp_size.y - exp_size.y * shiftExp) + sf::Vector2f(3, 8));
		target.draw(exp);

		//Make dynamic texts
		sf::Text hp_val = ParseStatistic("", player.getStatistics()["HP"], "/", player.getStatistics()["MaxHP"], "", 16);
		sf::Text mp_val = ParseStatistic("", player.getStatistics()["MP"], "/", player.getStatistics()["MaxMP"], "", 16);
		sf::Text lvl_val = ParseStatistic(" ", player.getPlayerInfo()["lvl"], " ", 28);
		sf::Text exp_val = ParseStatistic(" ", shiftExp * 100, " %", 16);
		sf::Text gold_val = ParseStatistic("", player.getPlayerInfo()["gold"], "", 16);

		//Get their positions
		sf::Vector2f hp_text_pos = getOffset(hp_val, bars_size, hp.getPosition() - sf::Vector2f(0,1));
		sf::Vector2f mp_text_pos = getOffset(mp_val, bars_size, mp.getPosition() - sf::Vector2f(0,1));
		sf::Vector2f lvl_text_pos = getOffset(lvl_val, main_section_size, sf::Vector2f(0, -main_section_size.y / 12));
		sf::Vector2f exp_text_pos = getOffset(exp_val, main_section_size, sf::Vector2f(0, main_section_size.y / 6));
		sf::Vector2f gold_text_pos = getOffset(gold_val, sf::Vector2f(0,0), position + sf::Vector2f(132, 94));

		//Draw dynamic values
		DrawLine(target, hp_text_pos, hp_val);
		DrawLine(target, mp_text_pos, mp_val);
		DrawLine(target, lvl_text_pos, lvl_val);
		DrawLine(target, exp_text_pos, exp_val);
		DrawLine(target, gold_text_pos, gold_val);
	}
}

sf::Text Hud::ParseStatistic(std::string prefix, int value1, std::string separator, int value2, std::string sufix, int fontSize) {
	//Parse format: PREFIX VALUE SEPARATOR VALUE2 SUFIX, f.e. Life: 34 / 100 %
	std::string line = prefix + std::to_string(value1) + separator + std::to_string(value2) + sufix;
	return sf::Text(line, font, fontSize);
}

sf::Text Hud::ParseStatistic(std::string prefix, int value, std::string sufix, int fontSize) {
	//Parse format: PREFIX VALUE SUFIX, f.e. Dodge: 34 %
	std::string line = prefix + std::to_string(value) + sufix;
	return sf::Text(line, font, fontSize);
}

void Hud::DrawLine(sf::RenderTarget& target, sf::Vector2f position, sf::Text text) {
	//Draw sf::Text
	text.setFont(font);
	text.setColor(sf::Color::White);
	text.setPosition(position);
	target.draw(text);
}

sf::Vector2f Hud::getTextSize(sf::Text object) {
	//Get size of Text object
	return sf::Vector2f(object.findCharacterPos(object.getString().getSize() - 1) - object.findCharacterPos(0));
}

sf::Vector2f Hud::getOffset(sf::Text object, sf::Vector2f size, sf::Vector2f offset) {	//offset_x by left, offset_y by top
	//Calculate offset, based on parent section size and offset
	sf::Vector2f result;
	result.x = offset.x + ((size.x - getTextSize(object).x) / 2);
	result.y = offset.y + ((size.y - object.getCharacterSize()) / 2);
	return result;
}