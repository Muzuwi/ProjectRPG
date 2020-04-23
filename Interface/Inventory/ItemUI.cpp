#include "Interface/Inventory/ItemUI.hpp"

ItemUI::ItemUI(const Item& toDisp)
: item(toDisp), font(AssetManager::getFont("ConnectionSerif")), active(false), mov(false), del(false), use(false)
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
	sf::CircleShape coin;
	coin.setFillColor(sf::Color(230, 181, 60));
	coin.setRadius(7);
	coin.setPosition(position + sf::Vector2f(size.x - 24, size.y - 24));
	target.draw(coin);

	//Draw buttons
	DrawButtons(target);

/* Control Shapes
	//DRAW ICON
	sf::RectangleShape icon;
	icon.setFillColor(sf::Color::White);
	icon.setPosition(position + sf::Vector2f(10, 10));
	icon.setSize(sf::Vector2f(32,32));
	target.draw(icon);
	// DRAW QUALITY
	sf::RectangleShape qual;
	qual.setFillColor(sf::Color::White);
	qual.setPosition(position + sf::Vector2f(48, 10));
	qual.setSize(quality.findCharacterPos(item.quality.size()) - quality.findCharacterPos(0) + sf::Vector2f(0,14));
	target.draw(qual);
	//DRAW NAME
	sf::RectangleShape obName;
	obName.setFillColor(sf::Color::White);
	obName.setPosition(position + sf::Vector2f(48, 28));
	obName.setSize(name.findCharacterPos(item.name.size()) - name.findCharacterPos(0) + sf::Vector2f(0,14));
	target.draw(obName);
	// DRAW Stats
	sf::RectangleShape st;
	st.setFillColor(sf::Color::White);
	st.setPosition(position + sf::Vector2f(10, 48));
	st.setSize(stats.findCharacterPos(item.stats.size()) - stats.findCharacterPos(0) + sf::Vector2f(0, 14));
	target.draw(st);
	// DRAW Description
	sf::RectangleShape ds;
	ds.setFillColor(sf::Color::White);
	ds.setPosition(position + sf::Vector2f(10, 48 + st.getSize().y + 8));
	ds.setSize(description.findCharacterPos(item.description.size()) - description.findCharacterPos(0) + sf::Vector2f(0, 14));
	target.draw(ds);
	// DRAW TYPE
	sf::RectangleShape typed;
	typed.setFillColor(sf::Color::White);
	typed.setPosition(position + sf::Vector2f(10, size.y - 24));
	typed.setSize(type.findCharacterPos(item.type.size()) - type.findCharacterPos(0) + sf::Vector2f(0, 14));
	target.draw(typed);
	// DRAW VALUE
	sf::RectangleShape val;
	val.setFillColor(sf::Color::White);
	val.setPosition(position + sf::Vector2f(size.x - 50, size.y - 24));
	val.setSize(value.findCharacterPos(item.value.size()) - value.findCharacterPos(0) + sf::Vector2f(0, 14));
	target.draw(val);
*/
}

void ItemUI::SelfInit() {
	//Quality
	quality.setFont(font);
	quality.setString(Item::getRarityString(item.getRarity()));
	quality.setFillColor(Item::getRarityColor(item.getRarity()));
	quality.setCharacterSize(16);

	//Name
	name.setFont(font);
	name.setString(item.getName());
	name.setFillColor(sf::Color::Black);
	name.setCharacterSize(15);

	//Stat
	stats.setFont(font);
	stats.setString(item.getStats());
	stats.setFillColor(sf::Color::White);
	stats.setCharacterSize(15);

	//Descr
	description.setFont(font);
	description.setString(item.getDescription());
	description.setFillColor(sf::Color::Black);
	description.setCharacterSize(15);

	//type
	type.setFont(font);
	type.setString(item.getTypeString(item.getType()));
	type.setFillColor(sf::Color::Black);
	type.setCharacterSize(15);

	//value
	value.setFont(font);
	value.setString(std::to_string(item.getValue()));
	value.setFillColor(sf::Color::Black);
	value.setCharacterSize(15);

	//SIZE AND POSITION
	double window_width = 200, window_height;
	stats_height = (stats.findCharacterPos(item.getStats().size()) - stats.findCharacterPos(0)).y;
	stats_height += 16;
	descript_height = (description.findCharacterPos(item.getDescription().size()) - description.findCharacterPos(0)).y;
	descript_height += 16;
	window_height = 158 + stats_height + descript_height;
	size += sf::Vector2f(window_width, window_height);
	position += sf::Vector2f(-(size.x - 5), 24);

	quality.setPosition(position + sf::Vector2f(48, 8));
	name.setPosition(position + sf::Vector2f(48, 26));
	stats.setPosition(position + sf::Vector2f(10, 46));
	description.setPosition(position + sf::Vector2f(10, 46 + stats_height));
	type.setPosition(position + sf::Vector2f(10, size.y - 26));
	value.setPosition(position + sf::Vector2f(size.x - 65, size.y - 26));

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