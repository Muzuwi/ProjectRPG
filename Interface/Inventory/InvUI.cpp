#include "InvUI.hpp"

InvUI::InvUI() { }

void InvUI::DrawSelf(sf::RenderTarget& target) {
	target.draw(title);
	DrawButtons(target);
	if (subWin.isActive()) {
		subWin.Draw(target);
	}
}

void InvUI::SelfInit() {
	title.setFont(font);
	title.setString("Inventory");
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(24);
	title.setPosition(sf::Vector2f(600.f, 15.f));
	SetButtons();
	sub = false;

	Item item("Ostrze burzy",
		"Legendarny",
		"One-Handed",
		"6900",
		"Attack: 3 - 5\nLightning: 1 - 2\nParry: 20%",
		"To legendarne ostrze\nzostalo wykute w\nniebianskiej kuzni\n600 lat temu.");
	backpack[0].setItem(item);
	backpack[0].getItem().Init("sword");
}

void InvUI::SetButtons() {
	focus = 0;
	sf::Vector2f size(32, 32);
	sf::Vector2f position(520, 50);

	for (int i = 0; i < 64; i++) {
		Cell acc;
		backpack.push_back(acc);
	}
	for (int i = 0; i < 64; i++) {
		backpack[i].Init(position + sf::Vector2f((i % 8 * 32), (i / 8 * 32)), size);
	}
	backpack[focus].SetFocus();
}

void InvUI::DrawButtons(sf::RenderTarget& target) {
	for (int i = 0; i < backpack.size(); i++) {
		backpack[i].Draw(target);
		backpack[i].getItem().Draw(backpack[i].GetPosition(),target);
	}
}

void InvUI::Update(int change) {
	backpack[focus].RemoveFocus();
	focus = focus + change;
	if (focus < 0) focus = backpack.size() + focus;
	else focus = focus % backpack.size();
	backpack[focus].SetFocus();
}

void InvUI::ProcessKey(sf::Event::KeyEvent key) {
	if (!subWin.isActive()) {
		if (key.code == sf::Keyboard::W) Update(-8);
		else if (key.code == sf::Keyboard::S) Update(8);
		else if (key.code == sf::Keyboard::A) Update(-1);
		else if (key.code == sf::Keyboard::D) Update(1);
		if (key.code == sf::Keyboard::Space) {
			if (!backpack[focus].isEmpty()) {
				subWin = backpack[focus].getItem();
				subWin.Init(backpack[focus].GetPosition(), sf::Vector2f(0, 0));
				subWin.ProcessKey(key);
			}
		}
	}
	else{
		subWin.ProcessKey(key);
	}
}