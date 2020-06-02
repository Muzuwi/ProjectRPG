#include "EnemyUI.hpp"

EnemyUI::EnemyUI(Actor* entity)
	: enemy(entity), font(AssetManager::getFont("VCR_OSD_MONO"))
{

}

void EnemyUI::SetEnemy(Actor* entity) {
	enemy = entity;
}

void EnemyUI::DrawSelf(sf::RenderTarget& target) {
	//Draw Content
	DrawPlayerInfo(target, position + sf::Vector2f(16, 8), 18);
	DrawStatistics(target, position + sf::Vector2f(16, 132), 16);
}

void EnemyUI::SelfInit() {
	//Getting sprites
	stat_icons.setTexture(AssetManager::getUI("stat_icons").getTexture());	//stat_icons
}

void EnemyUI::DrawIcon(sf::RenderTarget& target, sf::Sprite& object, int index, sf::Vector2f position, sf::Vector2f size) {
	object.setTextureRect(sf::IntRect(index * 32, 0, size.x, size.y));
	object.setColor(sf::Color(255, 255, 255, 160));
	object.setPosition(position);
	target.draw(object);
}

void EnemyUI::DrawPlayerInfo(sf::RenderTarget& target, sf::Vector2f offset, int font_size) {
	//Name
	sf::Text name("Przeciwnik", font, font_size + 1);
	name.setFillColor(sf::Color::Black);
	name.setPosition(offset);
	target.draw(name);

	//Level
	offset += sf::Vector2f(0, font_size + 4);//

	//HP
	offset += sf::Vector2f(0, font_size + 4);
	DrawIcon(target, stat_icons, 0, offset, sf::Vector2f(32, 32));
	int maxhp = enemy->getStatistics()["MaxHP"];
	int hp = enemy->getStatistics()["HP"];
	DrawLine(target, offset + sf::Vector2f(28, 8), ParseText(hp, maxhp, font_size - 2, "", "/"), sf::Color::Red);
	DrawBar(target, offset + sf::Vector2f(0, 28), hp, maxhp, sf::Vector2f(size.x - 32, 4), sf::Color::Red);

	//MP
	offset += sf::Vector2f(0, 32);
	DrawIcon(target, stat_icons, 1, offset, sf::Vector2f(32, 32));
	int maxmp = enemy->getStatistics()["MaxMP"];
	int mp = enemy->getStatistics()["MP"];
	DrawLine(target, offset + sf::Vector2f(28, 8), ParseText(mp, maxmp, font_size - 2, "", "/"), sf::Color::Blue);
	DrawBar(target, offset + sf::Vector2f(0, 28), mp, maxmp, sf::Vector2f(size.x - 32, 4), sf::Color::Blue);
}

void EnemyUI::DrawStatistics(sf::RenderTarget& target, sf::Vector2f position, int font_size) {

	//=============================== DATA ===============================//
		//KEYS FOR STATISTIC MAP
	std::vector<std::string> statIndex{ "HP","MaxHP",
										"MP","MaxMP",
										"Attack",
										"Fire",
										"Water",
										"Lightning",
										"AttackSpeed",
										"Armor",
										"Resistance",
										"Critical",
										"Dodge"
	};
	//=========================== END OF DATA =============================//

	for (int i = 4; i < statIndex.size(); i++) {
		//Draw Icon
		DrawIcon(target, stat_icons, i - 2, position + sf::Vector2f(2, 2), sf::Vector2f(32, 32));

		//Get Base statistic
		double middle = enemy->getStatistics()[statIndex[i]];

		std::string sufix = "";						//Default suffix
		int ceil = int(middle + (middle * 0.15));	//ceil of middle
		int floor = int(middle - (middle * 0.15));	//floor of middle

		//Drawing and calculating depends of mechanic basis and kind of statistic
		switch (i) {
		case 4:		//Physical - Damage from 85% to 115% of middle value
			DrawLine(target, position + sf::Vector2f(32, 8), ParseText(floor, ceil, font_size, "", "-"));
			break;
		case 5:		//Fire - Damage from 85% to 115% of middle value
			DrawLine(target, position + sf::Vector2f(32, 8), ParseText(floor, ceil, font_size, "", "-"));
			break;
		case 6:		//Water	- Damage smaller but static, + reducting AS
			DrawLine(target, position + sf::Vector2f(32, 8), ParseText(middle, font_size, ""));
			break;
		case 7:		//Lighning - Huge damage, but from 0 to middle value
			DrawLine(target, position + sf::Vector2f(32, 8), ParseText(0, middle, font_size, "", "-"));
			break;
		case 8:		//Attack speed - static value
			DrawLine(target, position + sf::Vector2f(32, 8), ParseText(middle, font_size, "", sufix));
			break;
		case 9:		//Armor - static value
			DrawLine(target, position + sf::Vector2f(32, 8), ParseText(middle, font_size, "", sufix));
			break;
		case 10:	//Resistance - static value in %
			sufix = "%";
			DrawLine(target, position + sf::Vector2f(32, 8), ParseText(middle, font_size, "", sufix));
			break;
		case 11:	//Critical - static value in %
			sufix = "%";
			DrawLine(target, position + sf::Vector2f(32, 8), ParseText(middle, font_size, "", sufix));
			break;
		case 12:	//Dodge - static value
			DrawLine(target, position + sf::Vector2f(32, 8), ParseText(middle, font_size, "", sufix));
			break;
		}

		//Update Pos
		position += sf::Vector2f{ 0.f, 22.f };
	}
}

void EnemyUI::DrawLine(sf::RenderTarget& target, sf::Vector2f position, sf::Text text, sf::Color color) {
	text.setFont(font);
	text.setColor(color);
	text.setPosition(position);
	target.draw(text);
}

void EnemyUI::DrawBar(sf::RenderTarget& target, sf::Vector2f position, int val1, int val2, sf::Vector2f size, sf::Color color) {
	//BACK
	Frame object_back;
	object_back.Init(position, size);
	object_back.Draw(target);
	//FILL
	double fill_width = (val1 / (double)val2) * (size.x - 2);
	sf::RectangleShape fill(sf::Vector2f(fill_width, size.y - 1));
	fill.setPosition(position + sf::Vector2f(1, 1));
	fill.setFillColor(color);
	target.draw(fill);
}

sf::Text EnemyUI::ParseText(int value1, int value2, int fontSize, std::string prefix, std::string separator, std::string sufix) {
	std::string line = prefix + std::to_string(value1) + separator + std::to_string(value2) + sufix;
	return sf::Text(line, font, fontSize);
}

sf::Text EnemyUI::ParseText(int value, int fontSize, std::string prefix, std::string sufix) {
	std::string line = prefix + std::to_string(value) + sufix;
	return sf::Text(line, font, fontSize);
}

sf::Vector2f EnemyUI::getTextSize(sf::Text object, std::string text) {
	return sf::Vector2f(object.findCharacterPos(text.size() - 1) - object.findCharacterPos(0));
}