#include "Interface/ItemUI.hpp"

ItemUI::ItemUI() { }

void ItemUI::DrawSelf(sf::RenderTarget& target) {
	//DRAW ICON
	sf::RectangleShape icon;
	icon.setFillColor(sf::Color::White);
	icon.setPosition(position + sf::Vector2f(10, 10));
	icon.setSize(sf::Vector2f(32,32));
	target.draw(icon);

	//DRAW QUALITY
	sf::RectangleShape qual;
	qual.setFillColor(sf::Color::White);
	qual.setPosition(position + sf::Vector2f(48, 10));
	qual.setSize(quality.findCharacterPos(quality_.size()) - quality.findCharacterPos(0) + sf::Vector2f(0,14));
	target.draw(qual);
	target.draw(quality);

	//DRAW NAME
	sf::RectangleShape obName;
	obName.setFillColor(sf::Color::White);
	obName.setPosition(position + sf::Vector2f(48, 28));
	obName.setSize(name.findCharacterPos(name_.size()) - name.findCharacterPos(0) + sf::Vector2f(0,14));
	target.draw(obName);
	target.draw(name);

	//DRAW Stats
	sf::RectangleShape line;
	line.setFillColor(sf::Color::White);
	for (int i = 0; i < stats.size(); i++) {
		stat.setString(stats[i]);
		stat.setPosition(position + sf::Vector2f(10, 46 + (i * 16)));
		line.setPosition(position + sf::Vector2f(10, 48 + (i * 16)));
		line.setSize(stat.findCharacterPos(stats[i].size()) - stat.findCharacterPos(0) + sf::Vector2f(0, 14));
		target.draw(line);
		target.draw(stat);
	}

	//DRAW Description

	for (int i = 0; i < description.size(); i++) {
		descript.setString(description[i]);
		descript.setPosition(position + sf::Vector2f(10, 46 + (i * 16)));
		line.setPosition(position + sf::Vector2f(10, 48 + (i * 16)));
		line.setSize(descript.findCharacterPos(description[i].size()) - descript.findCharacterPos(0) + sf::Vector2f(0, 14));
		target.draw(line);
		target.draw(descript);
	}

	//DRAW TYPE
	sf::RectangleShape typed;
	typed.setFillColor(sf::Color::White);
	typed.setPosition(position + sf::Vector2f(10, size.y - 24));
	typed.setSize(type.findCharacterPos(type_.size()) - type.findCharacterPos(0) + sf::Vector2f(0, 14));
	target.draw(typed);
	target.draw(type);

	//DRAW VALUE
	sf::RectangleShape val;
	val.setFillColor(sf::Color::White);
	val.setPosition(position + sf::Vector2f(size.x - 50, size.y - 24));
	val.setSize(value.findCharacterPos(value_.size()) - value.findCharacterPos(0) + sf::Vector2f(0, 14));
	target.draw(val);
	target.draw(value);

}

void ItemUI::SelfInit() {
	//SIZE AND POSITION
	double minW = 200;
	double w, h;
	w = (name.findCharacterPos(name_.size()) - name.findCharacterPos(0) + sf::Vector2f(58, 0)).x;
	h = 158 + (statLines * 16.0) + (descLines * 16.0);	//16*lines
	if (w < minW) w = minW;
	size += sf::Vector2f(w, h);
	position += sf::Vector2f(-(size.x - 5), 30);

	//CONTENT
	string temp;
	for (int i = 0; i < statLines; i++) {
		temp = "Statistic no. ";
		temp = temp + to_string(i);
		stats.push_back(temp);
	}
	for (int i = 0; i < descLines; i++) {
		temp = "Description line no. ";
		temp = temp + to_string(i);
		stats.push_back(temp);
	}

	font.loadFromFile("GameContent/Fonts/arial.ttf");

	//Quality
	quality.setFont(font);
	quality.setString(quality_);
	quality.setFillColor(sf::Color::Black);
	quality.setCharacterSize(15);
	quality.setPosition(position + sf::Vector2f(48, 8));

	//Name
	name.setFont(font);
	name.setString(name_);
	name.setFillColor(sf::Color::Black);
	name.setCharacterSize(15);
	name.setPosition(position + sf::Vector2f(48, 26));

	//Stat
	stat.setFont(font);
	stat.setFillColor(sf::Color::Black);
	stat.setCharacterSize(15);

	//Descr
	descript.setFont(font);
	descript.setFillColor(sf::Color::Black);
	descript.setCharacterSize(15);

	//type
	type.setFont(font);
	type.setString(type_);
	type.setFillColor(sf::Color::Black);
	type.setCharacterSize(15);
	type.setPosition(position + sf::Vector2f(10, size.y - 26));

	//value
	value.setFont(font);
	value.setString(value_);
	value.setFillColor(sf::Color::Black);
	value.setCharacterSize(15);
	value.setPosition(position + sf::Vector2f(size.x - 50, size.y - 26));
}