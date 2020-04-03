#include "InvUI.hpp"

InvUI::InvUI() { }

void InvUI::DrawSelf(sf::RenderTarget& target) {
	target.draw(title);
	DrawButtons(target);
}

void InvUI::SelfInit() {
	title.setFont(font);
	title.setString("Inventory");
	title.setFillColor(sf::Color::Black);
	title.setCharacterSize(24);
	title.setPosition(sf::Vector2f(600.f, 25.f));
	SetButtons();
}

void InvUI::SetButtons() {
	focus = 0;
	sf::Vector2f size(32, 32);
	sf::Vector2f position(520, 100);

	for (int i = 0; i < 64; i++) {
		Button acc("");
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
	}
}

void InvUI::Update(int change) {
	backpack[focus].RemoveFocus();
	focus = focus + change;
	if (focus < 0) focus = backpack.size() + focus;
	else focus = focus % backpack.size();
	backpack[focus].SetFocus();
}

void InvUI::Call() {
	//Obs³uga Przycisków
	cout << "Calling " << focus << " cell in inventory." << endl;
}

void InvUI::ProcessKey(sf::Event::KeyEvent key) {
	if (key.code == sf::Keyboard::W) Update(-8);
	else if (key.code == sf::Keyboard::S) Update(8);
	else if (key.code == sf::Keyboard::A) Update(-1);
	else if (key.code == sf::Keyboard::D) Update(1);
	else if (key.code == sf::Keyboard::Space) Call();
}