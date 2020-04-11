#include "Interface/ItemUI.hpp"

ItemUI::ItemUI(Item toDisp) : item(toDisp), active(false) { }

void ItemUI::DrawSelf(sf::RenderTarget& target) {
	/*DRAW ICON
	sf::RectangleShape icon;
	icon.setFillColor(sf::Color::White);
	icon.setPosition(position + sf::Vector2f(10, 10));
	icon.setSize(sf::Vector2f(32,32));
	target.draw(icon);
	*/
	Frame iconBack;
	iconBack.Init(position + sf::Vector2f(10, 10), sf::Vector2f(32, 32));
	iconBack.Draw(target);
	item.Draw(position + sf::Vector2f(10, 10), target);

	/* DRAW QUALITY
	sf::RectangleShape qual;
	qual.setFillColor(sf::Color::White);
	qual.setPosition(position + sf::Vector2f(48, 10));
	qual.setSize(quality.findCharacterPos(item.quality.size()) - quality.findCharacterPos(0) + sf::Vector2f(0,14));
	target.draw(qual);
	*/
	target.draw(quality);

	/* DRAW NAME
	sf::RectangleShape obName;
	obName.setFillColor(sf::Color::White);
	obName.setPosition(position + sf::Vector2f(48, 28));
	obName.setSize(name.findCharacterPos(item.name.size()) - name.findCharacterPos(0) + sf::Vector2f(0,14));
	target.draw(obName);
	*/
	target.draw(name);

	/* DRAW Stats
	sf::RectangleShape st;
	st.setFillColor(sf::Color::White);
	st.setPosition(position + sf::Vector2f(10, 48));
	st.setSize(stats.findCharacterPos(item.stats.size()) - stats.findCharacterPos(0) + sf::Vector2f(0, 14));
	target.draw(st);
	*/
	target.draw(stats);

	/* DRAW Description
	sf::RectangleShape ds;
	ds.setFillColor(sf::Color::White);
	ds.setPosition(position + sf::Vector2f(10, 48 + st.getSize().y + 8));
	ds.setSize(description.findCharacterPos(item.description.size()) - description.findCharacterPos(0) + sf::Vector2f(0, 14));
	target.draw(ds);
	*/
	target.draw(description);

	/* DRAW TYPE
	sf::RectangleShape typed;
	typed.setFillColor(sf::Color::White);
	typed.setPosition(position + sf::Vector2f(10, size.y - 24));
	typed.setSize(type.findCharacterPos(item.type.size()) - type.findCharacterPos(0) + sf::Vector2f(0, 14));
	target.draw(typed);
	*/
	target.draw(type);

	/* DRAW VALUE
	sf::RectangleShape val;
	val.setFillColor(sf::Color::White);
	val.setPosition(position + sf::Vector2f(size.x - 50, size.y - 24));
	val.setSize(value.findCharacterPos(item.value.size()) - value.findCharacterPos(0) + sf::Vector2f(0, 14));
	target.draw(val);
	*/
	target.draw(value);
	sf::CircleShape coin;
	coin.setFillColor(sf::Color(230, 181, 60));
	coin.setRadius(7);
	coin.setPosition(position + sf::Vector2f(size.x - 24, size.y - 24));
	target.draw(coin);

	//Draw buttons
	DrawButtons(target);
}

void ItemUI::SelfInit() {
	item.Init("sword");

	//CONTENT
	font.loadFromFile("GameContent/Fonts/ConnectionSerif.otf");

	//Quality
	quality.setFont(font);
	quality.setString(item.quality);
	if(item.quality == "Legendarny") quality.setFillColor(sf::Color::Red);
	else if(item.quality == "Unikat") quality.setFillColor(sf::Color::Green);
	else if(item.quality == "Rzadki") quality.setFillColor(sf::Color::Yellow);
	else if(item.quality == "Magiczny") quality.setFillColor(sf::Color::Blue);
	else if(item.quality == "Pospolite") quality.setFillColor(sf::Color::White);
	quality.setCharacterSize(16);

	//Name
	name.setFont(font);
	name.setString(item.name);
	name.setFillColor(sf::Color::Black);
	name.setCharacterSize(15);

	//Stat
	stats.setFont(font);
	stats.setString(item.stats);
	stats.setFillColor(sf::Color::White);
	stats.setCharacterSize(15);

	//Descr
	description.setFont(font);
	description.setString(item.description);
	description.setFillColor(sf::Color::Black);
	description.setCharacterSize(15);

	//type
	type.setFont(font);
	type.setString(item.type);
	type.setFillColor(sf::Color::Black);
	type.setCharacterSize(15);

	//value
	value.setFont(font);
	value.setString(item.value);
	value.setFillColor(sf::Color::Black);
	value.setCharacterSize(15);

	//SIZE AND POSITION
	double w = 200, h;
	statW = (stats.findCharacterPos(item.stats.size()) - stats.findCharacterPos(0)).y + 14 + 8;
	descW = (description.findCharacterPos(item.description.size()) - description.findCharacterPos(0)).y + 14 + 8;
	h = 158 + statW + descW;
	size += sf::Vector2f(w, h);
	position += sf::Vector2f(-(size.x - 5), 30);

	quality.setPosition(position + sf::Vector2f(48, 8));
	name.setPosition(position + sf::Vector2f(48, 26));
	stats.setPosition(position + sf::Vector2f(10, 46));
	description.setPosition(position + sf::Vector2f(10, 46 + statW));
	type.setPosition(position + sf::Vector2f(10, size.y - 26));
	value.setPosition(position + sf::Vector2f(size.x - 65, size.y - 26));

	//Buttons
	SetButtons();
}

void ItemUI::SetButtons() {
	focus = 0;

	//Creating Buttons
	sf::Vector2f size(35, 35);
	Button b0("leave");	//leave
	Button b1("move");	//move
	Button b2("use");	//use
	Button b3("del");	//delete

	//Remembering buttons
	buttons.push_back(b0);
	buttons.push_back(b1);
	buttons.push_back(b2);
	buttons.push_back(b3);

	//Initializing
	sf::Vector2f position(position + sf::Vector2f(10, statW + descW + 52));
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].Init(position, size);
		position += sf::Vector2f(40, 0);
	}
	buttons[focus].SetFocus();
}

void ItemUI::ProcessKey(sf::Event::KeyEvent key) {
	if (key.code == sf::Keyboard::Space) Call();
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
		active = !active;
		break;
	case 1:	//move
		break;
	case 2:	//use
		break;
	case 3:	//delete
		break;
	}
}

void ItemUI::DrawButtons(sf::RenderTarget& target) {
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].Draw(target);
	}
}