#include "Interface/Inventory/ItemUI.hpp"

ItemUI::ItemUI(const Item& toDisp)
: item(toDisp), font(AssetManager::getFont("Browser-Cyberlink-New")), active(false), mov(false), del(false), use(false)
{

}

void ItemUI::DrawSelf(sf::RenderTarget& target) {
	//Drawing Icon
	Frame iconBack;
	iconBack.Init(position + sf::Vector2f(10, 10), sf::Vector2f(32, 32));
	iconBack.Draw(target);
	item.draw(target, position + sf::Vector2f(10, 10));

	//Draw Rarity
	target.draw(quality);

	//Draw Name
	target.draw(name);

	//Draw Stats
	target.draw(stats);

	//Draw Description
	target.draw(description);

	//Draw Type
	target.draw(type);

	//Draw Value
	target.draw(value);
	coin.setTexture(AssetManager::getUI("coin").getTexture());
	coin.setPosition(position + sf::Vector2f(size.x - 26, size.y - 26));
	target.draw(coin);

	//Draw buttons
	DrawButtons(target);
}

void ItemUI::SelfInit() {
	//Quality
	quality = sf::Text(Item::getRarityString(item.getRarity()), font, 16);
	quality.setFillColor(Item::getRarityColor(item.getRarity()));

	//Name
	name = sf::Text(item.getName(), font, 15);
	name.setFillColor(sf::Color::Black);

	//Stat
	stats = sf::Text(item.getStats(), font, 15);
	stats.setFillColor(sf::Color::White);


	//Descr
	description = sf::Text(item.getDescription(), font, 15);
	description.setFillColor(sf::Color::Black);

	//type
	type = sf::Text(item.getTypeString(item.getType()), font, 15);
	type.setFillColor(sf::Color::Black);

	//value
	value = sf::Text(std::to_string(item.getValue()), font, 15);
	value.setFillColor(sf::Color::Black);

	//SIZE AND POSITION
	double window_width = 200;
	
	sf::Vector2f name_size = getContentSize(item.getName(), 15);
	if (name_size.x + 70 > window_width) window_width = name_size.x + 70;
	sf::Vector2f stat_size = getContentSize(item.getStats(), 15);
	if (stat_size.x + 30 > window_width) window_width = stat_size.x + 30;
	sf::Vector2f desc_size = getContentSize(item.getDescription(), 15);
	if (desc_size.x + 30 > window_width) window_width = desc_size.x + 30;
	stats_height = stat_size.y;
	descript_height = desc_size.y;


	size = sf::Vector2f(window_width, stat_size.y + desc_size.y + 158);
	position += sf::Vector2f(-(size.x - 5), 24);

	quality.setPosition(position + sf::Vector2f(48, 8));
	name.setPosition(position + sf::Vector2f(48, 26));
	stats.setPosition(position + sf::Vector2f(10, 46));
	description.setPosition(position + sf::Vector2f(10, 46 + stat_size.y));
	type.setPosition(position + sf::Vector2f(10, size.y - 26));
	value.setPosition(position + sf::Vector2f(size.x - 40, size.y - 26) - sf::Vector2f(getTextSize(value).x, 0) );

	//Buttons
	SetButtons();
}

void ItemUI::SetButtons() {
	focus = 0;

	//Creating Buttons
	sf::Vector2f size(35, 35);
	Button b0("inv_icons", 0);	//leave
	Button b1("inv_icons", 1);	//move
	Button b2("inv_icons", 2);	//use
	Button b3("inv_icons", 3);	//delete

	//Remembering buttons
	buttons.push_back(b0);
	buttons.push_back(b1);
	buttons.push_back(b2);
	buttons.push_back(b3);

	//Initializing
	sf::Vector2f newPos(position + sf::Vector2f(10, stats_height + descript_height + 52));
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].Init(newPos, size);
		newPos += sf::Vector2f(48, 0);
	}
	buttons[focus].SetFocus();
}

void ItemUI::ProcessKey(sf::Event::KeyEvent key) {
	if (key.code == sf::Keyboard::Space) Call();
	if (key.code == sf::Keyboard::Escape) active = !active;
	else {
		if (key.code == sf::Keyboard::D) Update(1);
		else if (key.code == sf::Keyboard::A) Update(-1);
	}
}

void ItemUI::Update(int change) {
	buttons[focus].RemoveFocus();
	focus = focus + change;
	if (focus < 0) focus = buttons.size() + focus;
	else focus = focus % buttons.size();
	buttons[focus].SetFocus();
}

void ItemUI::Call() {
	switch (focus) {
	case 0:	//leave
		break;
	case 1:	//move
		mov = true;
		break;
	case 2:	//use
		use = true;
		break;
	case 3:	//delete
		del = true;
		break;
	}
	active = !active;
}

void ItemUI::DrawButtons(sf::RenderTarget& target) {
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].Draw(target);
	}
}

sf::Vector2f ItemUI::getContentSize(std::string content, int fontsize) {

	sf::Text object;
	object.setFont(font);
	object.setCharacterSize(fontsize);
	object.setString(content);

	double object_height =(object.findCharacterPos(content.size()) - object.findCharacterPos(0)).y + 16;
	double object_width = 0;

	int begin_line = 0;
	for (int i = 0; i < content.size(); i++) {
		if (content[i] == '\n' or i == content.size() - 1) {
			double line_width = (object.findCharacterPos(i) - object.findCharacterPos(begin_line)).x;
			if (line_width > object_width) object_width = line_width;
			begin_line = i + 1;
		}
	}

	return sf::Vector2f(object_width, object_height);
}

sf::Vector2f ItemUI::getTextSize(sf::Text object) {
	return sf::Vector2f(object.findCharacterPos(object.getString().getSize() - 1) - object.findCharacterPos(0));
}